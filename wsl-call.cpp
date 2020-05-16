#include <windows.h> 
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

typedef  char const* PCSTR;
inline bool     isSeparator( char c ){ return c == '/' || c == '\\'; }
inline char*    lastNameInPath( char* path )
{
    char* p = path + strlen(path) - 2;
    for( ;p > path; p-- )
        if( isSeparator(*p))
            return ++p;
    return path;
}
class string: public std::string
{
public:
    string(std::string const& s) : std::string(s){}
    operator const char* () { return c_str(); }
    string operator + (const  char*  s) { return operator+( std::string(s) ); }
    string operator + (string const& s) { return string( (std::string)(*this) + (std::string)s ); }
};
void writeFile( char const* fileName, char const* str )
{
    FILE* fptr = fopen( fileName, "w" );

    if (fptr == NULL) {
        printf("Error writing to file %s", fileName );
        exit(1);
    }
    fprintf(fptr, "%s", str);
    fclose(fptr);
}
inline std::string file2str(const char* path) {
    std::ifstream input(path);
    std::stringstream sstr;
    while (input >> sstr.rdbuf());
    return sstr.str();
}
string wslPath(string name)
{
    string fileName = name + ".wslpath";
    string ret(file2str(fileName));

    return ret.size() > 0 ? ret : name;
}
int main( int argc, char* argv[], char* envp[] )
{
    PVOID OldValue = NULL;
    Wow64DisableWow64FsRedirection(&OldValue); // needed only for 32 bit binary

    string origName(lastNameInPath(argv[0]));
    string name = origName.substr(0, origName.find_last_of('.'));

    string winDir = string(getenv("SystemRoot"));
    string cmd = winDir + "\\System32\\wsl.exe ";
    if( strstr(argv[0], "wsl-call.exe") )
    {
        if (argc < 2)
        {   printf("\
Run `wsl-call.exe -all` to create windows EXE aliases for default linux instance binaries in current directory.\n\
Do not forget to put this directory in windows PATH.\n\
`wsl-call.exe <command>...` will create EXE alias for given one or more linux command.");
            return 0;
        }
        if( strstr( argv[1], "-all" ) )
        {   
            printf("Please wait, listing could take a while.\n\n");

            writeFile("wsl-call.sh", "compgen -ac|while read file; do fullname=`which $file` ; if ! [[ $fullname =~ /mnt/ ]]; then cp -s -f wsl-call.exe $file.exe; echo \"$file.exe = $fullname\"; fi; done");
            cmd = winDir + "\\System32\\wsl.exe bash wsl-call.sh";
            system(cmd.c_str());
            return 0;
        }
        for( int i = 1; i < argc; i++ )
        {
            string name( lastNameInPath(argv[i]) );
            writeFile( name + ".wslpath", argv[i] );
            string c = cmd + "cp -s -f wsl-call.exe " + name + ".exe";
            system( c );
            printf("%s\n", argv[i]);
        }
        return 0;
    }
    cmd = cmd + wslPath(name);

    for( int i = 1; i < argc; i++ )
        cmd = cmd + " " + argv[i];

    return system(cmd.c_str());
}
