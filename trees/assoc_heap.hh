template <typename _Tp, typename _Sequence = vector<_Tp>,
          typename _T_Hash = hash<_Tp>>
class assoc_heap {
private:
    template <typename T> static constexpr auto __map_types(T _t) {
        return make_tuple(std::priority_queue<_Tp, _Sequence, T>(_t));
    }
    template <typename T, typename... U> static constexpr auto __map_types(T _t, U... _o) {
        return tuple_cat(make_tuple(std::priority_queue<_Tp, _Sequence, T>(_t)), __map_types(_o...));
    }

    template <typename T> static constexpr void __push(_Tp _val, T& _c) {
        _c.push(_val);
    }

    template <typename T, typename... U> static constexpr void __push(_Tp _val, T& _c, U&... _o) {
        __push(_val, _c);
        __push(_val, _o...);
    }

    template <typename _Tc, typename _T_CC> class __assoc_heap {
    private:
        _Tc _content;
        _T_CC _comp;
        unordered_map<_Tp, size_t, _T_Hash> _count;
        size_t _size;

        template <size_t i> void __roll() {
            while (get<i>(_content).size() && !_count[get<i>(_content).top()]) {
                get<i>(_content).pop();
            }
        }
    public:
        __assoc_heap(_Tc _content, _T_CC _comp) :
            _content(_content), _comp(_comp), _size(0) {}

        template <size_t i> constexpr _Tp top() {
            __roll<i>();
            return get<i>(_content).top();
        }

        template <size_t i> constexpr void pop() {
            __roll<i>();
            _count[get<i>(_content).top()] -= 1;
            --_size;
            get<i>(_content).pop();
        }

        constexpr void push(_Tp __val) {
            _count[__val] += 1;
            ++_size;
            apply([&] (auto&... cs) { __push(__val, cs...); }, _content);
        }

        constexpr size_t size() const {
            return _size;
        }

        constexpr bool empty() const {
            return !_size;
        }

        template <typename... T> constexpr void emplace(T... _val) {
            push(_Tp(_val...));
        }
    };

public:
    template<typename... _T_cs> static auto make(tuple<_T_cs...> _comp) {
        auto _container = apply([&](auto... all) { return __map_types(all...); }, _comp);
        return __assoc_heap<decltype(_container), tuple<_T_cs...>>(_container, _comp);
    }
};
