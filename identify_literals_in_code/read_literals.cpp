#include <fstream>
using namespace std;

#define HEXA 16
#define OCTA 8
#define DECI 0

bool is_valid_int(int mode, char c)
{
    switch (mode)
    {
        case DECI: /* 0-9 */
            if ( c >= 48 && c <= 57)
                return true;
            break;
        case OCTA: /* 0-7 */
            if ( c >= 48 && c <= 55)
                return true;
            break;
        case HEXA: /* 0-9, A-F, a-f */
            if ( (c >= 48 && c <= 57) ||
                 ( c>= 65 && c <= 70) ||
                 (c >= 97 && c <= 102) )
                return true;
            break;
        default:
            break;
    }
    return false;
}

bool is_delimit_int(int mode, char c)
{
    //VALID Delimiters: ASCII: 32, !=, 37, 38, 40-43, 45, 47, 59-62, 124
    if (c == 32 || c == 37 || c ==38 || (c>=40 && c<=43) || c==45 || c==47 || (c>=59 && c<=62) || c==124)
        return true;
    return false;
}

bool is_valid_suffix(string suffix)
{

    if (suffix == "u" || suffix == "l" || suffix == "ul" || suffix == "ull")
        return true;
    return false;
}

void read_literals(char *file)
{
    ifstream source_file;
    source_file.open(file);
    //Error check

    ofstream myfile;
    myfile.open("literals.txt");
    //Eror check

    string line;
    int mode;
    bool cont;

    while(getline(source_file, line))
    {
        //cout<<line.size()<<'\n';
        for (int i=0;i<line.size();)
        {
            //cout<<line[i]<<" ";
            /* Integer Literal */
            if (line[i] >= 48 && line[i] <= 57)
            {
                mode = DECI;
                string num, suffix;
                if (line[i] == '0')
                {
                    //if (i != line.size()-1)

                    char dummy = line[i+1];
                    if (dummy == 'x' || dummy == 'X')
                    {
                        mode = HEXA;
                        num.push_back('0');num.push_back(dummy);
                        i+=2;
                    }
                    else
                        mode = OCTA;
                }

                cont = 1;
                while(cont)
                {
                    if (is_valid_int(mode, line[i]))
                        num.push_back(line[i]);
                    else if (num.size() && (i >= line.size() || is_delimit_int(mode, line[i])) )
                    {
                        myfile<<num<<suffix<<'\n';
                        cont = 0;
                    }
                    else if (line[i] == 'u' || line[i] == 'U' || line[i] == 'l' || line[i] == 'L')
                    {
                        suffix.push_back(line[i]);
                        if (!is_valid_suffix(suffix))
                            cont = 0;
                    }
                    else
                        cont = 0;
                    i++;
                }
            }
            /* String Literal */
            else if (line[i] == '"')
            {
                i++;
                string str;
                bool esc_seq = 0;
                while(true)
                {
                    if (line[i] == '\\') /* \\ represents \ */
                        esc_seq = 1;
                    else if (esc_seq)
                    {
                        str.push_back(line[i]);
                        esc_seq = 0;
                    }
                    else if (line[i] == '"')
                    {
                        myfile<<str<<'\n';
                        i++;
                        break;
                    }
                    str.push_back(line[i]);
                    i++;
                }
            }
            else
                i++;
        }
    }

    source_file.close();
    myfile.close();
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1; /*Error*/
    read_literals(argv[1]);
    return 0; /* Success */
}