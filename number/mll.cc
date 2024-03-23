template <ll mdl> struct MLL {
    ll val;
    MLL(ll v = 0) : val(mod(v, mdl)) {}
    MLL operator+(const MLL& rhs) { return mod(val + rhs.val, mdl); }
    MLL operator-(const MLL& rhs) { return mod(val - rhs.val, mdl); }
    MLL operator*(const MLL& rhs) { return mod(val * rhs.val, mdl); }
    MLL operator/(const MLL& rhs) { return mod(val * mod(inverse(rhs.val, mdl), mdl), mdl); }
    MLL operator%(const MLL& rhs) { return mod(val - (*this / rhs).val, mdl); }
    void operator+=(const MLL& rhs) { val = (*this + rhs).val; }
    void operator-=(const MLL& rhs) { val = (*this - rhs).val; }
    void operator*=(const MLL& rhs) { val = (*this * rhs).val; }
    void operator/=(const MLL& rhs) { val = (*this / rhs).val; }
    void operator%=(const MLL& rhs) { val = (*this % rhs).val; }
};

template <ll mdl>
ostream& operator<<(ostream& out, const MLL<mdl>& num) {
    return out << num.val;
}
