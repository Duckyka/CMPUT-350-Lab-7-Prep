#ifndef PACK_H
#define PACK_H

#include <tuple>
#include <type_traits>

namespace pack_detail
{
    //1. Size
    template <typename... Args>
    constexpr int packSize = sizeof...(Args);


    //2. Index to type
    //Base declaration
    template <int QueryIndex, typename... Args>
    struct _packIndexToType;

    //Recursive case
    template <int QueryIndex, typename Arg, typename... Args>
    struct _packIndexToType<QueryIndex, Arg, Args...>
    {
        using type = typename _packIndexToType<QueryIndex - 1, Args...>::type;
    };

    //Base case when index = 0
    template <typename Arg, typename... Args>
    struct _packIndexToType<0, Arg, Args...>
    {
        using type = Arg;
    };

    //Convenience alias
    template <int QueryIndex, typename... Args> using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;


    //3. Type to index
    template <typename QueryType, int Index, typename... Args>
    struct pack_type_to_index_helper;

    template <typename QueryType, int Index, typename... Args>
    struct pack_type_to_index_helper<QueryType, Index, QueryType, Args...> {
        static constexpr int value = Index;
    };

    template <typename QueryType, int Index, typename First, typename... Args>
    struct pack_type_to_index_helper<QueryType, Index, First, Args...> {
        static constexpr int value = pack_type_to_index_helper<QueryType, Index + 1, Args...>::value;
    };

    template <typename QueryType, int Index>
    struct pack_type_to_index_helper<QueryType, Index> {
        static constexpr int value = -1;
    };

    template <typename QueryType, typename... Args>
    constexpr int packTypeToIndex = pack_type_to_index_helper<QueryType, 0, Args...>::value;
}

template <typename... Args>
struct Pack
{
    static constexpr int size = sizeof...(Args);

    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    template <typename QueryType>
    static constexpr int index = [] {
        constexpr int result = pack_detail::packTypeToIndex<QueryType, Args...>;
        return result;
    }();
};

#endif  // PACK_H
