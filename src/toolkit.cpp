#include "toolkit.h"

String getMiddleText(String src, String text1, String text3)
{
    int s = src.indexOf(text1);
    int e = src.indexOf(text3, s);
    String text2 = src.substring(s + text1.length(), e);
    return text2;
}

String fixTurkishLetters(String text)
{
    String result = text;

    result.replace("İ", "I");
    result.replace("Ğ", "G");
    result.replace("Ü", "U");
    result.replace("Ş", "S");
    result.replace("Ö", "O");
    result.replace("Ç", "C");

    result.replace("ı", "i");
    result.replace("ğ", "g");
    result.replace("ü", "u");
    result.replace("ş", "s");
    result.replace("ö", "o");
    result.replace("ç", "c");

    return result;
}

String eventLookup(String code)
{
    if (code.equals("\"CB\""))
    {
        return "Çok Bulutlu";
    }
    else if (code.equals("\"CB\""))
    {
        return "Çok Bulutlu";
    }
    else if (code.equals("\"PB\""))
    {
        return "Parçalı Bulutlu";
    }
    else if (code.equals("\"AB\""))
    {
        return "Az bulutlu";
    }
    else if (code.equals("\"CB\""))
    {
        return "Çok Bulutlu";
    }
    else if (code.equals("\"A\""))
    {
        return "Açık";
    }
    else if (code.equals("\"PUS\""))
    {
        return "Puslu";
    }
    else if (code.equals("\"GSY\""))
    {
        return "Gökgürültülü Sağanak Yaşığlı";
    }
    else if (code.equals("\"KKY\""))
    {
        return "Karla Karışık Yağmur";
    }
    else if (code.equals("\"Y\""))
    {
        return "Yağışlı";
    }
    else if (code.equals("\"SY\""))
    {
        return "Sağanak Yağışı";
    }
    else if (code.equals("\"K\""))
    {
        return "Karlı";
    }
    else if (code.equals("\"DY\""))
    {
        return "Dolu Yağışlı";
    }
    else if (code.equals("\"F\""))
    {
        return "Fırtınalı";
    }
    else if (code.equals("\"R\""))
    {
        return "Rüzgarlı";
    }
    else
        return code;
}
