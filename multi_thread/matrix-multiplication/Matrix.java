
public abstract class Matrix {
    public final int row;
    public final int col;

    public Matrix(final int row, final int col) {
        this.row = row;
        this.col = col;
    }

    /** Returns the value at the specified position; both row and col start from 1. */
    public abstract double at(final int row, final int col) throws IndexException;

    @Override
    public String toString() {
        final char SEP = ' ';
        final char END = '\n';
        StringBuilder builder = new StringBuilder(this.row * this.col * 2);  /* at least: one digit each + one sep each */
        for (int i = 1; i <= this.row; ++i) {
            for (int j = 1; j <= this.col; ++j) {
                builder.append(String.format("%.2f%c", this.at(i, j), SEP));
            }
            builder.append(END);
        }
        return builder.toString();
    }

    /**
     * Returns true if both `row` and `col` are positive and not greater
     * than `this.row` and `this.col`, respectively.
     */
    protected boolean isValidIndex(final int row, final int col) {
        return 1 <= row && row <= this.row && 1 <= col && col <= this.col;
    }

    /** Indicates that an invaild index is used. */
    public class IndexException extends RuntimeException {
        public IndexException() {
            super(String.format("index should be positive and in range (row, col): (%d, %d)",
                                Matrix.this.row, Matrix.this.col));
        }
    }
}
