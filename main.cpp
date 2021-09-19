#include<bits/stdc++.h>
using namespace std;
#define MAX 100000 
int n=0,level;
char a[100000];
int casenum[100],casen=0;
int ifelsen=0,ifelseifn=0;
stack<int> st;
struct key   //结构体数组,关键字按顺序排列
{
 char *word;
 int count;
} keytab[] = {
"auto",0,"break",0,"case",0,"char",0,"const",0,
"continue",0,"default",0,"do",0,"double",0,
"else",0,"enum",0,"extern",0,"float",0,"for",0,
"goto",0,"if",0,"int",0,"long",0,"register",0,
"return",0,"short",0,"signed",0,"sizeof",0,
"static",0,"struct",0,"switch",0,"typedef",0,
"union",0,"unsigned",0,"void",0,"volatile",0,"while",0,
};

//关键字的个数等于数组的长度除以单个元素的长度
#define NKEYS (sizeof keytab / sizeof(struct key))

int j=0;
int getword(char *word, int lim){
    char *w = word;
    for( j;j<n;j++){
    if(isspace(a[j]))
	   continue;
	else break;//忽略空白符
 }
     
    *w++ = a[j];
    if (!isalpha(a[j])){          //当前不是字母的情况 
        *w = '\0';
        return a[j++];
    }
     j++;
     for ( ; --lim > 0; w++){
     if (!isalnum(*w = a[j++])){  //当前不是字母或数字时，该单词结束
        j--;
        break;
        }
    }
    *w = '\0';                    //字符串结束符'\0'
}

/* binsearch:  find word in tab[0]...tab[n-1] */
//折半查找
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high)
 {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int flag=0;
void pop0(){
	while(st.empty()<=0){
		int p=st.top();
		st.pop();
		if(p==2){
			flag=1;
		}
		if(p==1){
			if(flag==1){
				ifelseifn++;
				flag=0;break; 
			}		   
		    if(flag==0){
			    ifelsen++;break;
			}	    		
		}	
	}
}


void count(){
    int m;int wordflag=0;
    char word[MAX],word0[MAX];//word0记录上一个单词 
    for(int i=0;i<n;i++)
{
    getword(word, MAX);
    if (isalpha(word[0])) //word的第一个为字母
        {
		if ((m = binsearch(word, keytab, NKEYS)) >= 0)
            {keytab[m].count++;//在结构体中查找成功，关键字计数加1
            
			if(strcmp(keytab[m].word,"case")==0)
			casenum[casen]++;
			if(strcmp(keytab[m].word,"switch")==0)
		    casen++;
			
			if(strcmp(keytab[m].word,"if")==0&&(strcmp(word0,"else")!=0||wordflag==1))
		    st.push(1);    //记录if为1  else if为2  else为3
			if(strcmp(keytab[m].word,"if")==0&&strcmp(word0,"else")==0&&wordflag==0)
		    st.push(2);  
			if((strcmp(keytab[m].word,"if")!=0||wordflag==1)&&strcmp(word0,"else")==0)
		    pop0();        //遇到else出栈 
			
			strcpy(word0,keytab[m].word);
			}
			wordflag=0;	//还原 wordflag
		} 
	else wordflag=1;//记录上一个word为非字母 
 }
 //统计结束，打印结果
    int sum=0;
    for (int i = 0; i < NKEYS;i++){
	sum+=keytab[i].count;
 }
    cout<<"total num:"<<sum<<endl;
    if(level>=2){
	cout<<"switch num:"<<keytab[25].count<<endl;
    cout<<"case num:";
    for(int k=1;k<=keytab[25].count;k++)
    cout<<casenum[k]<<" ";
    cout<<endl;
 }
    if(level>=3){
	pop0();
 	cout<<"if-else num:"<<ifelsen<<endl;
 }
    if(level==4){
 	cout<<"if-elseif-else num:"<<ifelseifn<<endl;
 }
}

void readtxt(string file)
{
    ifstream infile; 
    infile.open(file.data());   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	char c;
    infile >> noskipws;
    while (!infile.eof())
    {
        infile>>c;
        a[n++]=c;
    }
	infile.close();    //关闭文件输入流   
    count();         
}

int main(){
	string s;
	cin>> s;
	cin>>level;
	readtxt(s);
	return 0;
}