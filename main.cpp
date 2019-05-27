#include <iostream>
#include <cstdio>
#include <cstring>
#include<vector>
using namespace std;

void enter(char filename[128]){
   for (bool valid = false; !valid;)
    {valid = true;
    cout << "Enter filename" << endl;
    cin>> filename;
    //�������� �� ������ �������
    const char* bansymbols= "*\"<>?|";
    for (int i = 0; i<6; i++){
        if (strchr(filename,bansymbols[i])){
      valid = false;
       cout<<"incorrect filename\n";
        }
    }
    //�������� �� ���������

    for (int i = 0; i<128; i++){
        if (filename[i] == ':') {
            if ((i!=1) || !isalpha(filename[0]) || (filename[2]!='\\')) {
                     valid = false;
                    cout<<"incorrect filename\n";
            }
        }
    }
    //�������� ����������
    const char* format = strrchr(filename,'.');
    const char* txt = ".txt";

     if (!strrchr(filename,'.') || strcmp(format,txt)){
    strcat(filename,txt);
    }

    }
}

size_t findtext(char str[128], char* data)
{
    size_t strlength = strlen(str);
    size_t occur = 0;
   for ( size_t i=0; data[i]!='\0';i++ )
   {
      for (size_t j =0; j<strlength;j++){
              if (data[i+j]==str[j]){
                if (j==strlength-1){occur++;};
              }else break;
      }
   }
   return occur;
}

int main()
{
    char filename[128];
    enter(filename);
    cout<<filename;

    FILE * file = fopen(filename, "r");

    fseek(file, SEEK_SET,SEEK_END-SEEK_SET);
    size_t length = ftell(file);
    length/=sizeof(char);

    char *data = new char[length];

   fseek(file,0,0);
     length = fread(data, sizeof(char),length,file);
    data[length]='\0';
    fclose(file);

    char usstring[128];
    cout << endl<< "Enter string" << endl;
    cin>> usstring;

  size_t occurcount = findtext(usstring, data);
    cout <<"Occurance number "<< occurcount;

    delete[] data;

    return 0;
}
