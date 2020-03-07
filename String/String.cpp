/*
    但凡是位置（pos）都是从1开始的
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define Status bool
#define initSize 100

class String
{
private:
    char *ch;
//     int length;
public:
    // char *ch;
    int length;
    Status StrAssign(char *c);
    Status StrCopy(String &T);
    Status StrEmpty();
    int StrCompare(int n,String S);
    int StrLength();
    Status ClearString();
    Status Concat(String S);
    String SubString(int pos,int len);
    int Index(String S,int pos);
    Status Replace(String S,String V);
    Status StrInsert(String S,int pos);
    Status Print();
    String();
    String (const String &copy);
    ~String();
};

String::String (const String& copy) 
{
    this->ch = (char*)malloc((copy.length+1)*sizeof(char));
    int i;
    for(i = 0; copy.ch[i] != '\0';i++){
        this->ch[i] = copy.ch[i];
    }
    this->ch[i] = '\0'; 
    this->length = copy.length;
}

String::String()
{
    this->ch = nullptr;
    this->length = 0;
}

String::~String()
{
    free(this->ch);
}

Status String::StrAssign(char *c){
    if(this->ch != nullptr) this->ClearString();
    int i;
    for(i = 0;c[i] != '\0';i++){}
    this->ch = (char*)malloc((i+1)*sizeof(char));
    for(i = 0;c[i] != '\0';i++) this->ch[i] = c[i];
    this->ch[i] = '\0';
    this->length = i;
    return this->ch == nullptr?false:true;
}

Status String::StrCopy(String &S){
}

Status String::StrEmpty(){
    return this->length == 0?true:false;
}
//n=0长度相比，n=1长度+内容相比
int String::StrCompare(int n,String S){
    if(n==0)
        return this->StrLength() - S.StrLength();
    else if(n==1)
    {
        if(this->StrLength() != S.StrLength()) 
        return this->StrLength() - S.StrLength();
        else
        {
            int i = 0;
            for ( i = 0; i < this->StrLength(); i++)
            {
                if(S.ch[i] != this->ch[i]) return -1;
            }
            return 0;
        }
    }
}

int String::StrLength(){
    return this->length;
}

Status String::ClearString(){
    free(this->ch);
    this->ch = nullptr;
    return this->ch == nullptr? true:false;
}

Status String::Concat(String S){
    this->ch = (char*)realloc(this->ch,(this->StrLength()+S.StrLength()+1)*sizeof(char));
    if(this->ch == nullptr) return false;
    int i,j;
    for(i = this->StrLength(),j = 0;i < this->StrLength()+S.StrLength();i++,j++){
        this->ch[i] = S.ch[j];
    }
    this->ch[i] = '\0';
    this->length = i;
    S.ch[0] = 'a';
    return true;
}

String String::SubString(int pos,int len){
    if(pos>=1 && pos<=this->StrLength() && len>=0 && len<=this->StrLength()-pos+1){
        pos-=1;
        char *chars = (char*)malloc((len+1)*sizeof(char));
        int i;
        for(i = pos;i < pos+len;i++) 
            chars[i - pos] = this->ch[i];
        chars[len] = '\0';
        String S;
        S.StrAssign(chars);
        return S;
    }
    else{
        String S;
        return S;
    }
}
//not KMP
int String::Index(String S,int pos){
    // if(S.StrLength() == 0) return 0;
    int i = pos;
    ////因为pos有2位偏移（1开始）所以这里要+2偏移
    while (i <= this->StrLength() - S.StrLength() + 1)
    {
        // String tmp = this->SubString(i,S.StrLength());
        if(S.StrCompare(1,this->SubString(i,S.StrLength())) == 0) 
            return i;
        else i++;
    }
    return -1;
}//KMP TODO!!!

Status String::Replace(String S,String V){
    if(S.StrCompare(0,V) < 0){
        int i = 1,num = 0;
        while (i != 0)
        {
            i = this->Index(S,i)+1;
            num++;
        }
        this->ch = (char*)realloc(this->ch,(num * abs(S.StrCompare(0,V)) + this->length + 1) * sizeof(char));
        i = this->Index(S,1);
        while (i != -1)
        {
            // for(int j = 0; j < V.StrLength() - S.StrLength(); j++){
            //     for (int k = this->StrLength()-1; k > i-1+S.StrLength(); k--) 
            //         this->ch[k] = this->ch[k];
            //     this->length++;
            // }
            for (int k = this->StrLength()-1; k >= i-1+S.StrLength(); k--) 
                this->ch[k + V.StrLength() - S.StrLength()] = this->ch[k];
            this->length+=V.StrLength() - S.StrLength();
            for (int k = i-1; k < i-1+V.StrLength(); k++)
                this->ch[k] = V.ch[k-i+1];
            i = this->Index(S,i);
        }
        this->ch[this->length] = '\0';
        return true;
    }
    else if(S.StrCompare(0,V) == 0){
        int i = this->Index(S,1);
        while (i != -1)
        {
            for (int k = i-1; k < i-1+V.StrLength(); k++)
                this->ch[k] = V.ch[k-i+1];
            i = this->Index(S,i);
        }
        this->ch[this->length] = '\0';
        return true;
    }
    else
    {
        int i = this->Index(S,1);
        while (i != -1)
        {   
            //O(N)同上优化！
            for(int j = 0; j < S.StrLength() - V.StrLength(); j++){
                //max(j) = S.length - V.length -1
                // S.length - j = S.length - S.length + V.length +1
                //(i-1) + V.length = S.length - j - 1
                for (int k = i-1+S.StrLength()-j-1; k < this->StrLength(); k++)
                    this->ch[k] = this->ch[k+1];
                this->length--;
            }
            for (int k = i-1; k < i-1+V.StrLength(); k++)
                this->ch[k] = V.ch[k-i+1];
            i = this->Index(S,i);
        }
        this->ch[this->length] = '\0';
        return true;
    }
    
    return false;
}

Status String::StrInsert(String S,int pos){
    if(pos-1<0 || pos>this->StrLength()-1) return false;
    if(!(this->ch = (char*)realloc(this->ch,(S.StrLength()+this->StrLength()+1)*sizeof(char)))) return false;
    this->length += S.StrLength(); 
    for (int i = this->StrLength()-1; i >= pos-1; i--)
        this->ch[i + S.StrLength()] = this->ch[i];
    for (int i = 0; i < S.StrLength(); i++)
        this->ch[i] = S.ch[i];
    return true;
}

Status String::Print(){
    printf("%s",this->ch);
    return true;
}

int main(){
    String S,T,X;
    S.StrAssign("abkkkab");
    T.StrAssign("zzzzzz");
    X.StrAssign("ab");
    S.Concat(X);
    // S.Concat(X);
    // S.Concat(X);
    // S.Concat(X);
    // S.Print();
    // X.Print();
    S.Replace(X,T);
    X.StrAssign("qnmlgb");
    S.StrInsert(X,1);
    S.Print();
    int x;
    scanf("%d",&x);
}