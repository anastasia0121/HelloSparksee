#include <iostream> 
#include <unistd.h>

void switch_keyboard_layout(const std::wstring &src, std::wstring &dst);
void switch_keyboard_layout1(const std::wstring &src, std::wstring &dst);

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

bool test_keyboard_layout_en_to_ru(void(&func)(const std::wstring &src, std::wstring &dst))
{
    std::wstring src, dst;

    src = L"qwertyuiop[]";
    func(src, dst);
    ASSERT(dst == L"йцукенгшщзхъ");

    src = L"asdfghjkl;'";
    func(src, dst);
    ASSERT(dst == L"фывапролджэ");

    src = L"zxcvbnm,.";
    func(src, dst);
    ASSERT(dst == L"ячсмитьбю");

    src = L"QWERTYUIOP{}";
    func(src, dst);
    ASSERT(dst == L"ЙЦУКЕНГШЩЗХЪ");

    src = L"ASDFGHJKL:\"";
    func(src, dst);
    ASSERT(dst == L"ФЫВАПРОЛДЖЭ");

    src = L"ZXCVBNM<>";
    func(src, dst);
    ASSERT(dst == L"ЯЧСМИТЬБЮ");

    return true;
}

bool test_keyboard_layout_ru_to_en(void(&func)(const std::wstring &src, std::wstring &dst))
{
    std::wstring src, dst;

    src = L"йцукенгшщзхъ";
    func(src, dst);
    ASSERT(dst == L"qwertyuiop[]");

    src = L"фывапролджэ";
    func(src, dst);
    ASSERT(dst == L"asdfghjkl;'");

    src = L"ячсмитьбю";
    func(src, dst);
    ASSERT(dst == L"zxcvbnm,.");

    src = L"ЙЦУКЕНГШЩЗХЪ";
    func(src, dst);
    ASSERT(dst == L"QWERTYUIOP{}");

    src = L"ФЫВАПРОЛДЖЭ0";
    func(src, dst);
    ASSERT(dst == L"ASDFGHJKL:\"0");

    src = L"ЯЧСМИТЬБЮ";
    func(src, dst);
    ASSERT(dst == L"ZXCVBNM<>");

    return true;
}

bool unit_test()
{
    if (!test_keyboard_layout_en_to_ru(switch_keyboard_layout)) return false;   
    if (!test_keyboard_layout_ru_to_en(switch_keyboard_layout)) return false;   
    if (!test_keyboard_layout_en_to_ru(switch_keyboard_layout1)) return false;   
    if (!test_keyboard_layout_ru_to_en(switch_keyboard_layout1)) return false;   

    return true;
}
