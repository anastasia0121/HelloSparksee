#include <iostream> 
#include "Wrapper.h"

#define ASSERT(x) \
    do {\
         std::cout << __func__ << "() " \
        << __FILE__ << ":"  << __LINE__ << " " \
        << ( x ? " passed (" : " failed (" ) << #x << ")"\
        << std::endl;\
        if (!(x))\
        {\
            return false; \
        }\
    } while (0)

bool test_keyboard_layout_en_to_ru()
{
    const DataManager *dtm = DataManager::get_instanse();
    std::wstring src, dst;

    src = L"qwertyuiop[]";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"йцукенгшщзхъ");

    src = L"asdfghjkl;'";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"фывапролджэ");
    
    src = L"zxcvbnm,.";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"ячсмитьбю");

    src = L"QWERTYUIOP{}";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"ЙЦУКЕНГШЩЗХЪ");

    src = L"ASDFGHJKL:\"";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"ФЫВАПРОЛДЖЭ");
    
    src = L"ZXCVBNM<>";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"ЯЧСМИТЬБЮ");

    return true;
}

bool test_keyboard_layout_ru_to_en()
{
    const DataManager *dtm = DataManager::get_instanse();
    std::wstring src, dst;

    src = L"йцукенгшщзхъ";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"qwertyuiop[]");

    src = L"фывапролджэ";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"asdfghjkl;'");
    
    src = L"ячсмитьбю";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"zxcvbnm,.");

    src = L"ЙЦУКЕНГШЩЗХЪ";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"QWERTYUIOP{}");

    src = L"ФЫВАПРОЛДЖЭ";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"ASDFGHJKL:\"");
    
    src = L"ЯЧСМИТЬБЮ";
    dtm->switch_keyboard_layout(src, dst);
    ASSERT(dst == L"ZXCVBNM<>");

    return true;
}

int main(int argc, char *argv[]) 
{
    if (!test_keyboard_layout_en_to_ru()) return -1;   
    if (!test_keyboard_layout_ru_to_en()) return -1;   

    return 0;
}
