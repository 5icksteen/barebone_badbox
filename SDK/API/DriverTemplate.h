#pragma once

class DriverTemplate
{
  int value_;

 public:
  // コンストラクタ
  DriverTemplate() {}
  //デストラクタ
  ~DriverTemplate() {}
  // コピーコンストラクタ
  DriverTemplate(DriverTemplate &) {}
  // コピー代入演算子
  DriverTemplate &operator=(DriverTemplate &) {}
  // ムーブコンストラクタ
  DriverTemplate(DriverTemplate &&) {}
  // ムーブ代入演算子
  DriverTemplate &operator=(DriverTemplate &&) {}

  DriverTemplate &init() { return *this; }

  DriverTemplate &set(int value)
  {
    this->value_ = value;
    return *this;
  }

  int get() { return value_; }

  //コピー代入演算子
  DriverTemplate &operator=(const DriverTemplate &rhs)
  {
    // __critical_section_enter();
    set(rhs.get());
    // __critical_section_exit();
    return *this;
  }

  DriverTemplate &operator=(int value)
  {
    set(value);
    return *this;
  }

  operator bool()
  {
    return get();
  }
};