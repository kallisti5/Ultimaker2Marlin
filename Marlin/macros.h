#ifndef MACROS_H
#define MACROS_H

// Macros for bit masks
#define BIT(b) (1<<(b))
#define TEST(n,b) (((n)&BIT(b))!=0)
#define SET_BIT(n,b,value) (n) ^= ((-value)^(n)) & (BIT(b))

// Macros for maths shortcuts
#define RADIANS(d) ((d)*M_PI/180.0)
#define DEGREES(r) ((r)*180.0/M_PI)

// Macros to contrain values
#define NOLESS(v,n) do{ if (v < n) v = n; }while(0)
#define NOMORE(v,n) do{ if (v > n) v = n; }while(0)

// Macros to support option testing
//#define _CAT(a, ...) a ## __VA_ARGS__
//#define SWITCH_ENABLED_0 0
//#define SWITCH_ENABLED_1 1
//#define SWITCH_ENABLED_  1
//#define ENABLED(b) _CAT(SWITCH_ENABLED_, b)
//#define DISABLED(b) (!_CAT(SWITCH_ENABLED_, b))

#define COUNT(a) (sizeof(a)/sizeof(*a))

template<typename T>
class restorer {
  T& ref_;
  T  val_;
public:
  restorer(T& perm) : ref_(perm), val_(perm) {}
  restorer(T& perm, T temp_val) : ref_(perm), val_(perm) { perm = temp_val; }
  ~restorer() { restore(); }
  inline void restore() { ref_ = val_; }
};

#define REMEMBER(N,X,V...) const restorer<typeof(X)> restorer_##N(X, ##V)
#define RESTORE(N) restorer_##N.restore()

#endif //__MACROS_H
