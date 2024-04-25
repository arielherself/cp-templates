template <ll mdl> struct MLL {
    ll val;
    MLL(ll v = 0) : val(mod(v, mdl)) {}
    MLL(const MLL<mdl>& other) : val(other.val) {}
    friend MLL operator+(const MLL& lhs, const MLL& rhs) { return mod(lhs.val + rhs.val, mdl); }
    friend MLL operator-(const MLL& lhs, const MLL& rhs) { return mod(lhs.val - rhs.val, mdl); }
    friend MLL operator*(const MLL& lhs, const MLL& rhs) { return mod(lhs.val * rhs.val, mdl); }
    friend MLL operator/(const MLL& lhs, const MLL& rhs) { return mod(lhs.val * mod(inverse(rhs.val, mdl), mdl), mdl); }
    friend MLL operator%(const MLL& lhs, const MLL& rhs) { return mod(lhs.val - (lhs / rhs).val, mdl); }
    friend bool operator==(const MLL& lhs, const MLL& rhs) { return lhs.val == rhs.val; }
    friend bool operator!=(const MLL& lhs, const MLL& rhs) { return lhs.val != rhs.val; }
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

template <ll mdl>
istream& operator>>(istream& in, MLL<mdl>& num) {
    return in >> num.val;
}
