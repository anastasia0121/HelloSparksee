#include <iostream> 
#include <cstdlib>
#include <stdlib.h>
#include <unordered_map>

static std::unordered_map<wchar_t, std::wstring> my_map
{
    {L'q',L"й"}, {L'w',L"ц"}, {L'e',L"у"}, {L'r',L"к"}, {L't',L"е"},
    {L'y',L"н"}, {L'u',L"г"}, {L'i',L"ш"}, {L'o',L"щ"}, {L'p',L"з"},
    {L'[',L"х"}, {L']',L"ъ"}, {L'a',L"ф"}, {L's',L"ы"}, {L'd',L"в"},
    {L'f',L"а"}, {L'g',L"п"}, {L'h',L"р"}, {L'j',L"о"}, {L'k',L"л"},
    {L'l',L"д"}, {L';',L"ж"}, {L'\'',L"э"}, {L'z',L"я"}, {L'x',L"ч"},
    {L'c',L"с"}, {L'v',L"м"}, {L'b',L"и"}, {L'n',L"т"}, {L'm',L"ь"},
    {L',',L"б"}, {L'.',L"ю"},

    {L'Q',L"Й"}, {L'W',L"Ц"}, {L'E',L"У"}, {L'R',L"К"}, {L'T',L"Е"},
    {L'Y',L"Н"}, {L'U',L"Г"}, {L'I',L"Ш"}, {L'O',L"Щ"}, {L'P',L"З"},
    {L'{',L"Х"}, {L'}',L"Ъ"}, {L'A',L"Ф"}, {L'S',L"Ы"}, {L'D',L"В"},
    {L'F',L"А"}, {L'G',L"П"}, {L'H',L"Р"}, {L'J',L"О"}, {L'K',L"Л"},
    {L'L',L"Д"}, {L':',L"Ж"}, {L'"',L"Э"}, {L'Z',L"Я"}, {L'X',L"Ч"},
    {L'C',L"С"}, {L'V',L"М"}, {L'B',L"И"}, {L'N',L"Т"}, {L'M',L"Ь"},
    {L'<',L"Б"}, {L'>',L"Ю"},

    {L'й',L"q"}, {L'ц',L"w"}, {L'у',L"e"}, {L'к',L"r"}, {L'е',L"t"},
    {L'н',L"y"}, {L'г',L"u"}, {L'ш',L"i"}, {L'щ',L"o"}, {L'з',L"p"},
    {L'х',L"["}, {L'ъ',L"]"}, {L'ф',L"a"}, {L'ы',L"s"}, {L'в',L"d"},
    {L'а',L"f"}, {L'п',L"g"}, {L'р',L"h"}, {L'о',L"j"}, {L'л',L"k"},
    {L'д',L"l"}, {L'ж',L";"}, {L'э',L"'"}, {L'я',L"z"}, {L'ч',L"x"},
    {L'с',L"c"}, {L'м',L"v"}, {L'и',L"b"}, {L'т',L"n"}, {L'ь',L"m"},
    {L'б',L","}, {L'ю',L"."},

    {L'Й',L"Q"}, {L'Ц',L"W"}, {L'У',L"E"}, {L'К',L"R"}, {L'Е',L"T"},
    {L'Н',L"Y"}, {L'Г',L"U"}, {L'Ш',L"I"}, {L'Щ',L"O"}, {L'З',L"P"},
    {L'Х',L"{"}, {L'Ъ',L"}"}, {L'Ф',L"A"}, {L'Ы',L"S"}, {L'В',L"D"},
    {L'А',L"F"}, {L'П',L"G"}, {L'Р',L"H"}, {L'О',L"J"}, {L'Л',L"K"},
    {L'Д',L"L"}, {L'Ж',L":"}, {L'Э',L"\""}, {L'Я',L"Z"}, {L'Ч',L"X"},
    {L'С',L"C"}, {L'М',L"V"}, {L'И',L"B"}, {L'Т',L"N"}, {L'Ь',L"M"},
    {L'Б',L"<"}, {L'Ю',L">"}
};

void switch_keyboard_layout1(const std::wstring &src, std::wstring &dst)
{
    dst.clear();
    std::wstring tmp;
    
    for (const auto &c :src)
    {
        tmp = my_map[c];
        dst += ( (tmp == L"") ? &c : tmp );
    }
}
