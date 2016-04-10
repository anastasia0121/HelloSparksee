#include <iostream> 

#include "gdb/Sparksee.h"
#include "gdb/Database.h"
#include "gdb/Session.h"
#include "gdb/Graph.h"
#include "gdb/Export.h"
#include "gdb/Objects.h"
#include "gdb/ObjectsIterator.h"
#include "io/CSVWriter.h"
#include "io/CSVReader.h"
#include "io/NodeTypeExporter.h"
#include "io/NodeTypeLoader.h"
#include "io/EdgeTypeExporter.h"
#include "io/EdgeTypeLoader.h"

#include <array>
#include <cstdlib>
#include <stdlib.h>

#include "MyExport.h"
#include "Wrapper.h"
#include "Type.h"

using namespace sparksee::gdb;
using namespace sparksee::io;

void DataManager::switch_keyboard_layout(std::wstring &src, std::wstring &dst) const
{
    dst.clear();

    for (const auto &c :src)
    {
        switch(c) 
        {
            case 'q': dst += L"й"; break;
            case 'w': dst += L"ц"; break;
            case 'e': dst += L"у"; break;
            case 'r': dst += L"к"; break;
            case 't': dst += L"е"; break;
            case 'y': dst += L"н"; break;
            case 'u': dst += L"г"; break;
            case 'i': dst += L"ш"; break;
            case 'o': dst += L"щ"; break;
            case 'p': dst += L"з"; break;
            case '[': dst += L"х"; break;
            case ']': dst += L"ъ"; break;
            case 'a': dst += L"ф"; break;
            case 's': dst += L"ы"; break;
            case 'd': dst += L"в"; break;
            case 'f': dst += L"а"; break;
            case 'g': dst += L"п"; break;
            case 'h': dst += L"р"; break;
            case 'j': dst += L"о"; break;
            case 'k': dst += L"л"; break;
            case 'l': dst += L"д"; break;
            case ';': dst += L"ж"; break;
            case '\'': dst += L"э"; break;
            case 'z': dst += L"я"; break;
            case 'x': dst += L"ч"; break;
            case 'c': dst += L"с"; break;
            case 'v': dst += L"м"; break;
            case 'b': dst += L"и"; break;
            case 'n': dst += L"т"; break;
            case 'm': dst += L"ь"; break;
            case ',': dst += L"б"; break;
            case '.': dst += L"ю"; break;

            case 'Q': dst += L"Й"; break;
            case 'W': dst += L"Ц"; break;
            case 'E': dst += L"У"; break;
            case 'R': dst += L"К"; break;
            case 'T': dst += L"Е"; break;
            case 'Y': dst += L"Н"; break;
            case 'U': dst += L"Г"; break;
            case 'I': dst += L"Ш"; break;
            case 'O': dst += L"Щ"; break;
            case 'P': dst += L"З"; break;
            case '{': dst += L"Х"; break;
            case '}': dst += L"Ъ"; break;
            case 'A': dst += L"Ф"; break;
            case 'S': dst += L"Ы"; break;
            case 'D': dst += L"В"; break;
            case 'F': dst += L"А"; break;
            case 'G': dst += L"П"; break;
            case 'H': dst += L"Р"; break;
            case 'J': dst += L"О"; break;
            case 'K': dst += L"Л"; break;
            case 'L': dst += L"Д"; break;
            case ':': dst += L"Ж"; break;
            case '"': dst += L"Э"; break;
            case 'Z': dst += L"Я"; break;
            case 'X': dst += L"Ч"; break;
            case 'C': dst += L"С"; break;
            case 'V': dst += L"М"; break;
            case 'B': dst += L"И"; break;
            case 'N': dst += L"Т"; break;
            case 'M': dst += L"Ь"; break;
            case '<': dst += L"Б"; break;
            case '>': dst += L"Ю"; break;

            default:  break;
        }
    }
}

