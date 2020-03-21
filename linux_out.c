////////////////////////////////////////////////////
//             (C) 2020 Ty Qualters               //
//      See LICENSE for license information       //
////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

enum LinuxStringColor { 
        Black = 0, Red = 1, Green = 2, Orange = 3, Blue = 4, Magenta = 5, Cyan = 6, None = 7
};
enum LinuxStringStyle {
        Normal = 0, Bold = 1, Dim = 2, Italic = 3, Underline = 4, Blinking = 5, Invert = 7, Invisible = 8
};

char* LinuxApplyStringStyle(char* str, enum LinuxStringColor color, enum LinuxStringStyle style, bool applyEndStyleTerminator)
{

        static const char* reset = "\033[m";
        static const char* start = "\033[#;3#m";
        static const char* start2 = "\033[#m";


        // set alloc to the size of the string + a null terminator
        size_t alloc = strlen(str) + 1;
        if(color != None) alloc += strlen(start);
        else alloc += strlen(start) -1;

        if(applyEndStyleTerminator) alloc += strlen(reset);

        char* newStr = (char*)malloc(alloc);

        if(color == None) 
        {
                memcpy(newStr, start2, (strlen(start2))*sizeof(char));
                memcpy(&newStr[strlen(start2)], str, strlen(str)*sizeof(char));
                memcpy(&newStr[strlen(start2) + strlen(str)], reset, strlen(reset)*sizeof(char));
                newStr[strlen(start2) + strlen(str) + strlen(reset)] = '\0';
        }else
        {
                memcpy(newStr, start, strlen(start)*sizeof(char));
                memcpy(&newStr[strlen(start)], str, strlen(str)*sizeof(char));
                memcpy(&newStr[strlen(start) + strlen(str)], reset, strlen(reset)*sizeof(char));
                newStr[strlen(start) + strlen(str) + strlen(reset)] = '\0';
                newStr[5] = color + '0';
        }
        newStr[2] = style + '0';
        return newStr;
}

char* joinStrs(int cstrs, char** strs, char delim)
{
        // i'd rather do 2 loops than dynamically allocate
        long newStrLen = 0;
        for(int i = 0; i < cstrs; ++i)
        {
                newStrLen += strlen(strs[i]) + 1; // delimiter
        }
        long index = 0;
        char* newStr = (char*)malloc(newStrLen * sizeof(char));
        for(int i = 0; i < cstrs; ++i)
        {
                memcpy(newStr, strs[i], strlen(strs[i]) * sizeof(char));
                newStr[strlen(strs[i])] = delim;
                index += strlen(strs[i]) + 1;
        }
        newStr[strlen(newStr) - 1] = '\0';
        return newStr;
}

char* toLowerCase(char* str)
{
        char* newStr = (char*)malloc(strlen(str)*sizeof(char));

        memcpy(newStr, str, strlen(str) * sizeof(char));

        for(long i = 0; i < strlen(str); ++i)
        {
                newStr[i] = tolower(str[i]);
        }
        return newStr;
}

int main(int argc, char** argv)
{

        enum LinuxStringColor color = None;
        enum LinuxStringStyle style = Normal;

        for(int i = 1; i < argc; ++i)
        {
                // search for -i
                // after that everything afterward is the content
                //
                // before -i
                // -- style=normal, bold, dim, italic, underlined, blinking, reverse, invisible
                // -- color=none,black,white,red,green,etc.


                if(strcmp(toLowerCase(argv[i]), "--help") == 0)
                {
                        printf("-s [Normal, \033[1mBold\033[m, \033[2mDim\033[m, \033[3mItalic\033[m, \033[4mUnderline\033[m, \033[5mBlinking\033[m, \033[7mInvert\033[m, Invisible]  -c [None, Black, \033[0;31mRed\033[m, \033[0;32mGreen\033[m, \033[0;34mBlue\033[m, \033[0;36mCyan\033[m, \033[0;33mOrange\033[m, \033[0;35mPurple\033[m] -i Your string to stylize!!! (Also accepts input.)\n");
                        return 0;
                }
                else if(strcmp(toLowerCase(argv[i]), "-c") == 0)
                {
                        if(i + 1 < argc)
                        {
                                if(strcmp(toLowerCase(argv[++i]), "none") == 0)
                                {
                                        color = None;
                                }
                                else if(strcmp(toLowerCase(argv[i]), "red") == 0)
                                {
                                        color = Red;
                                }
                                else if(strcmp(toLowerCase(argv[i]), "black") == 0)
                                {
                                        color = Black;
                                }
                                else if(strcmp(toLowerCase(argv[i]), "green") == 0)
                                {
                                        color = Green;
                                }
                                else if(strcmp(toLowerCase(argv[i]), "blue") == 0)
                                {
                                        color = Blue;
                                }
                                else if(strcmp(toLowerCase(argv[i]), "cyan") == 0)
                                {
                                        color = Cyan;
                                }
                                else if(strcmp(toLowerCase(argv[i]), "orange") == 0)
                                {
                                        color = Orange;
                                }
                                else if(strcmp(toLowerCase(argv[i]), "purple") == 0)
                                {
                                        color = Magenta;
                                }
                                else
                                {
                                        printf("Invalid argument: %s\nExpected a color: [None, Black, \033[0;31mRed\033[m, \033[0;32mGreen\033[m, \033[0;34mBlue\033[m, \033[0;36mCyan\033[m, \033[0;33mOrange\033[m, \033[0;35mPurple\033[m]\n", argv[i]);
                                        return -1;
                                }
                        }
                        else
                        {
                                printf("Too few arguments. Caught color flag without following color.\n");
                                return -1;
                        }
                }
                else if(strcmp(toLowerCase(argv[i]), "-s") == 0)
                {
                        if(i + 1 < argc)
                        {
                                if(strcmp(toLowerCase(argv[++i]), "normal") == 0)
                                {
                                        style = Normal;
                                }
                                else if(strcmp(toLowerCase(argv[i]), "bold") == 0)
                                {
                                        style = Bold;
                                }
                                else if(strcmp(toLowerCase(argv[i]), "dim") == 0)
                                {
                                        style = Dim;
                                }else if(strcmp(toLowerCase(argv[i]), "italic") == 0)
                                {
                                        style = Italic;
                                }else if(strcmp(toLowerCase(argv[i]), "underline") == 0)
                                {
                                        style = Underline;
                                }else if(strcmp(toLowerCase(argv[i]), "blinking") == 0)
                                {
                                        style = Blinking;
                                }else if(strcmp(toLowerCase(argv[i]), "reverse") == 0)
                                {
                                        style = Invert;
                                }else if(strcmp(toLowerCase(argv[i]), "invisible") == 0)
                                {
                                        style = Invisible;
                                }
                                else
                                {
                                        printf("Invalid argument: %s\nExpected a style: [Normal, \033[1mBold\033[m, \033[2mDim\033[m, \033[3mItalic\033[m, \033[4mUnderline\033[m, \033[5mBlinking\033[m, \033[7mInvert\033[m, Invisible]\n", argv[i]); 
                                }
                        }
                        else
                        {
                                printf("Too few arguments. Caught style flag without following style.\n");
                                return -1;
                        }
                }
                else if(strcmp(toLowerCase(argv[i]), "-i") == 0)
                {
                        char* joinedStr = joinStrs(argc - i, &argv[++i], ' ');
                        char* styledStr = LinuxApplyStringStyle( joinedStr, color, style, true );
                        printf("%s\n", styledStr);
                        return 0;
                }
                else
                {
                        printf("Unexpected argument: %s\n", argv[i]);
                        return -1;
                }

        }
        char buffer[4096 * 16];
        fgets(buffer, sizeof(buffer), stdin);
        char* styledStr = LinuxApplyStringStyle( &buffer[0], color, style, true );
        printf("%s", styledStr);
        return 0;
}
