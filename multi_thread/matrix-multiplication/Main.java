import java.time.Duration;
import java.time.Instant;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;


public class Main {
    private static final Matrix A = new Matrix(50, 8000) {
        @Override
        public double at(final int row, final int col) {
            if (!this.isValidIndex(row, col)) {
                throw new Matrix.IndexException();
            }
            return 6.6 * row - 3.3 * col;
        }
    };

    private static final Matrix B = new Matrix(8000, 50) {
        @Override
        public double at(final int row, final int col) {
            if (!this.isValidIndex(row, col)) {
                throw new Matrix.IndexException();
            }
            return 100 + 2.2 * row - 5.5 * col;
        }
    };

    /* run our tasks in reusable-threads from pool for better efficiency */
    private static ExecutorService pool;

    public static void main(String[] args) throws Exception {
        /* timing */
        System.out.format(String.join("\n",
                "Elapsed time:",
                "  for-loop: %.2f ms",
                "  thread-per-row: %.2f ms",
                "  thread-per-block: %.2f ms"),
                countElapsedTime(Main::multWithForLoop),
                countElapsedTime(Main::multWithThreadsPerRow),
                countElapsedTime(Main::multWithThreadsPerBlock));
        /* testing */
        // checkCorrectnessOfResultsFromThreadWithResultFromLoop();
    }

    /** Calculates matrix multiplication with simply a 3-level nested loop. */
    private static double[][] multWithForLoop() {
        double[][] result = new double[A.row][B.col];
        for (int i = 1; i <= A.row; ++i) {
            for (int j = 1; j <= B.col; ++j) {
                for (int k = 1; k <= A.col; ++k) {
                    result[i - 1][j - 1] += A.at(i, k) * B.at(k, j);
                }
            }
        }
        return result;
    }

    /** Calculates matrix multiplication with threads for every single row. */
    private static double[][] multWithThreadsPerRow()
            throws InterruptedException {
        pool = Executors.newCachedThreadPool();
        double[][] result = new double[A.row][B.col];  /* shared by threads */
        for (int i = 1; i <= A.row; ++i) {
            /* take a thread from the pool and assign task to it:
                calculates a single row */
            pool.execute(new PartialRowMatMultRunnable(i) {
                @Override
                public void run() {
                    result[this.row - 1] = multRow(this.row);
                }
            });
        }
        /* Wait until all threads finish their task, which means the matrix
            multiplication is completed. */
        waitAllTasksInPool();
        return result;
    }

    /** Calculates a single row of the matrix multiplication. */
    private static double[] multRow(final int row) {
        double[] result = new double[B.col];
        for (int j = 1; j <= B.col; ++j) {
            for (int k = 1; k <= A.col; ++k) {
                result[j - 1] += A.at(row, k) * B.at(k, j);
            }
        }
        return result;
    }

    /** Calculates matrix multiplication with threads for every single block. */
    private static double[][] multWithThreadsPerBlock()
            throws InterruptedException {
        /* 5 x 5, assume that the diemensions are always multiple of 5 */
        final int BLOCK_SIZE = 5;
        pool = Executors.newCachedThreadPool();
        double[][] result = new double[A.row][B.col];  /* shared by threads */
        for (int i = 1; i < A.row; i = i + BLOCK_SIZE) {
            for (int j = 1; j < B.col; j = j + BLOCK_SIZE) {
                /* take a thread from the pool and assign task to it:
                    calculates a single block */
                pool.execute(new PartialBlockMatMultRunnable(
                        new IndexInterval(i, i + BLOCK_SIZE),
                        new IndexInterval(j, j + BLOCK_SIZE)) {
                    @Override
                    public void run() {
                        multBlock(result, this.row, this.col);
                    }
                });
            }
        }
        waitAllTasksInPool();
        return result;
    }

    /** Calculates a single block of the matrix multiplication. */
    private static void multBlock(double[][] result, final IndexInterval row,
                                  final IndexInterval col) {
        for (int i = row.begin; i < row.end; ++i) {
            for (int j = col.begin; j < col.end; ++j) {
                for (int k = 1; k <= A.col; ++k) {
                    result[i - 1][j - 1] += A.at(i, k) * B.at(k, j);
                }
            }
        }
    }

    /** Returns how much time is spent by `target` in milliseconds. */
    private static double countElapsedTime(final ThrowableCallback target)
            throws Exception {
        final Instant start = Instant.now();
        target.call();
        final Instant end = Instant.now();
        return Duration.between(start, end).toNanos() / 1000000.f;
    }

    /**
     * Returns after all tasks in `pool` are completed or timeout occurs.
     * @throws InterruptedException: if interrupted while waiting.
     */
    private static void waitAllTasksInPool() throws InterruptedException {
        pool.shutdown();  /* disable new tasks from being executed */
        /* wait a while for existing tasks to terminate */
        if (!pool.awaitTermination(1, TimeUnit.SECONDS)) {
            /* timeout, cancel currently executing tasks */
            pool.shutdownNow();
        }
    }

    /**
     * Compares the equalness of the results of `multWithThreadsPerRow()`
     * and `multWithThreadsPerBlock()` with the result of `multWithForLoop()`
     * since we're confident that the result of multWithForLoop is always correct.
     *
     * Note that this is a time consuming method.
     */
    private static void checkCorrectnessOfResultsFromThreadWithResultFromLoop()
            throws InterruptedException {
        double[][] c = multWithForLoop();
        double[][] c2 = multWithThreadsPerRow();
        double[][] c3 = multWithThreadsPerBlock();

        for (int i = 0; i < A.row; ++i) {
            for (int j = 0; j < B.col; ++j) {
                if (Double.compare(c[i][j], c2[i][j]) != 0
                        || Double.compare(c[i][j], c3[i][j]) != 0) {
                    System.err.println("result from threading fails");
                    System.err.format("%f, %f\n", c2[i][j], c3[i][j]);
                }
            }
        }
    }
}


/**
 * The Runnable used to calculate a single row of the matrix in thread.
 * It knows the row number of the target row.
 */
abstract class PartialRowMatMultRunnable implements Runnable {
    final int row;

    PartialRowMatMultRunnable(final int row) {
        this.row = row;
    }
}

/**
 * The Runnable used to calculate a single block of the matrix in thread.
 * It knows the interval of the target block.
 */
abstract class PartialBlockMatMultRunnable implements Runnable {
    final IndexInterval row;
    final IndexInterval col;

    PartialBlockMatMultRunnable(final IndexInterval row, final IndexInterval col) {
        this.row = row;
        this.col = col;
    }
}


class IndexInterval {
    final int begin;
    final int end;

    public IndexInterval(final int begin, final int end) {
        this.begin = begin;
        this.end = end;
    }
}


interface ThrowableCallback {
    void call() throws Exception;
}
