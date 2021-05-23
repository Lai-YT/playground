class Base {
public:
  Base() = delete;

  Base(int i) noexcept
    :i_(i) {}

  virtual ~Base() = default;

  int i() const {
    return i_;
  }

private:
  int i_;
};


class Derived final : public Base {
public:
  Derived() = delete;

  Derived(int i) noexcept
    :Base(i) {}

  ~Derived() = default;
};
