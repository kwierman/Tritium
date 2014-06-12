#ifndef TriNull_h_
#define TriNull_h_

namespace TritiumDesign{

    ///Dummy Null Class
    struct TriNullType{};
    class TriEmptyType {};
        
    
    inline bool operator==(const TriEmptyType&, const TriEmptyType&){return true;}   

    inline bool operator<(const TriEmptyType&, const TriEmptyType&){return false;}

    inline bool operator>(const TriEmptyType&, const TriEmptyType&){return false;}

}


#endif //TriNull_h_