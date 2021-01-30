#include <iostream>
#include <cstdio> //IO
#include <vector>

using namespace std;

vector<int> lps; //longest proper prefix wich is also a suffix

void preProcessLPSArray(string pattern){
    int sizePattern = pattern.length();
    int length = 0;
    int i = 1;
    lps[0] = 0; //always be 0 'cause doesn't have a previous comparable string
    
    //O(M)
    while (i < sizePattern){
        if (pattern[i] == pattern[length]){
            length++;
            lps[i++] = length;
        } else {
            if (length != 0){
                length = lps[length - 1]; //compares with the previous ones
            } else {
                lps[i++] = 0;
            }
        }
    }
}

//O(N + M)
void kmpSearch(string pattern, string text){
    int sizePattern = pattern.length();
    int sizeText = text.length();
    int i = 0, j = 0;

    preProcessLPSArray(pattern);

    while(i < sizeText){
       if (pattern[j] != text[i]){
            if (j != 0)
                j = lps[j - 1]; //lps[j-1] characters will match anyway
            else
                i++;
        } else {
            j++; i++;
            
            if (j == sizePattern){
                 cout << "O padrao foi encontrado na posicao " << (i - j) << endl;
                 j = lps[j - 1];
            }
        }
    }
}

int main(){
    string pattern;
    string text;

    cin >> text;
    cin >> pattern;

    lps.resize(pattern.length());

    kmpSearch(pattern, text);

    return 0;
}

