#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
typedef struct
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;
void Select(HuffmanTree HT,int i,int *s1,int *s2)
	//在HT[1..i]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
{
	int j,k;
	k=HT[i].weight;
	for(j=1;j<=i;j++)
		if(HT[j].weight<=k&&HT[j].parent==0)
			{
				k=HT[j].weight;
				*s1=j;
		     }//找权值最小的结点
    HT[*s1].parent++;
	for(j=i;j>=1;j--)
		if(HT[j].parent==0)
			{
			   k=HT[j].weight;
			   break;
		    }//找一个parent为0的结点
	 for(j=1;j<=i;j++)
		if(HT[j].weight<=k&&HT[j].parent==0)
			{
				k=HT[j].weight;
				*s2=j;
		     }//找权值最小的另一结点
}//Select
void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n)
	//w存放n个字符的权值(>0),构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
{
	int m,i,start,f,c,s1,s2;
	char *cd;
	HuffmanTree p;
	m=2*n-1;//m为赫夫曼树结点的总个数，n为叶子结点数
	*HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//0号单元未用
	for(p=(*HT)+1,i=1;i<=n;i++,++p,++w)
	{
		(*p).weight=*w;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
	}
	for(;i<=m;++i,++p)
	{
		(*p).weight=0;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
	}
	for(i=n+1;i<=m;++i)
	{
		Select(*HT,i-1,&s1,&s2);//在HT[1..i-1]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
		(*HT)[s1].parent=i;
		(*HT)[s2].parent=i;
		(*HT)[i].lchild=s1;
		(*HT)[i].rchild=s2;
		(*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
	}//建赫夫曼树
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char *));//分配n个字符编码的头指针向量
	cd=(char *)malloc(n*sizeof(char));//分配求编码的工作空间
	cd[n-1]='\0';//编码结束符
	for(i=1;i<=n;i++)
	{
		start=n-1;//编码结束符位置
		for(c=i,f=(*HT)[i].parent;f!=0;c=f,f=(*HT)[f].parent)//从叶子到根逆向求编码
			if((*HT)[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
		(*HC)[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy((*HC)[i],&cd[start]);//从cd复制编码到HC
	}
	free(cd);//释放工作空间
}//HuffmanCoding
void compress(FILE *fp1,FILE *fp2)
	//对以fp1为文件指针的文件进行压缩，压缩后的文件为fp2
{
	HuffmanTree HT;HuffmanCode HC;
	int i,j,n,s,k,t,w[256],weight[256],ch,num;
	char *p;
	for(i=0;i<256;i++)
		w[i]=0;//对每个字符的频率初始化
	num=0;//文件所含字符数初始化为0
	while(1)
	{
		ch=fgetc(fp1);
		if(feof(fp1)) break;
		w[ch]++;//统计文件中每个字符的频率
		num++;//统计文件中字符的个数
	}
	n=0;
	for(i=0;i<256;i++)
		if(w[i]!=0)
		{
		  weight[n]=w[i];
		  n++;
		}//求出频率不为0的字符的个数（为n）并将相应的频率存入数组weight[]中
   if(n==0)
	{
	printf("该文件为空文件，不需压缩。\n");
	system("pause");
	exit(0);
	}//空文件不压缩，直接退出
	else 
	{
	 fprintf(fp2,"%d ",num);
	 fprintf(fp2,"%d",n);
	 for(i=0;i<256;i++)
	   if(w[i]!=0)
        fprintf(fp2,"%c",i);
	 for(i=0;i<256;i++)
	   if(w[i]!=0)
         fprintf(fp2,"%d ",w[i]);//以上是将文件的总长度、字符种类、字符、字符频率存入压缩文件
  if(n>1)//当字符个数>1的时候，构造赫夫曼树进行压缩
 {
    HuffmanCoding(&HT,&HC,weight,n);//数组weight[]存放n个字符的权值(>0),构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
	 i=s=0;
	 rewind(fp1);//使位置指针重新返回到文件的开头
     while(1)
   {
	 ch=fgetc(fp1);
	 if(feof(fp1)) break;
	 k=0;
	 for(j=0;j<=ch;j++)
		if(w[j]!=0)
			k++;//字符ch是文件中第k个频率不为0的字符（按ASCII码顺序）
	 for(p=HC[k];*p!='\0';p++)
	 {
	   t=*p-'0';
	   s=s<<1;
	   s=s+t;
	   i++;
	   if(i==8)//当编码数为8时将其作为一个字节存入到压缩文件中
	   {
		 fputc(s,fp2);
		 s=0;
		 i=0;
		}//if
	  }//for
   }//while
   if(i<8)
  {
	 s=s<<(8-i);
     fputc(s,fp2);
  }//将不足8位的编码用0补齐
 }//if(n>1)
  fclose(fp1);
  fclose(fp2);
 }//else
}//compress
void decompress(FILE *fp2,FILE *fp3)
{
   int i,j,n,number,ch,num,c,bit[8],w[256];
   char f[257];//与哈夫曼编码中0号单元不用保持一致
   HuffmanTree HT,q;HuffmanCode HC;
   fscanf(fp2,"%d",&num);//读入文件总的字符个数
   fscanf(fp2,"%d",&n);//读入文件中所含字符的种类
   for(i=1;i<=n;i++)
      fscanf(fp2,"%c",&f[i]);//将文件中的字符存入数组f[]
   for(i=0;i<n;i++)
	  fscanf(fp2,"%d",&w[i]);//每个字符的权重存入数组w[]
   if(n==1)
	  for(i=0;i<w[0];i++)
		fputc(f[1],fp3);//当文件只有一种字符时，直接输出
   else
   {
   HuffmanCoding(&HT,&HC,w,n);//w存放n个字符的权值(>0),构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
   q=&HT[2*n-1];//q指向根结点
   number=0;
   ch=fgetc(fp2);//读取一个额外输入的空格
   while(1)
{
	ch=fgetc(fp2);
	if(feof(fp2)) break;
	i=7;
	while(i>=0)
	{
	 c=ch%2;
     ch=ch/2;
	 bit[i]=c;
	 i--;
	}//将字符转换成对应的编码
	for(i=0;i<8;i++)
	{
	  if(q->lchild==0&&q->rchild==0)//q为叶子结点
	   for(j=1;j<=n;j++)
		if(q==&HT[j])
		{
		if(number<num)//已输出的字符数小于原文件的总字符数时，则继续输出
	   {
		 fprintf(fp3,"%c",f[j]);
		 number++;
	   }
	    q=&HT[2*n-1];break;//重新将q指向根结点便于下次继续寻找
		}//if
	if(bit[i]==0)
	  q=&HT[q->lchild];//编码为0找左孩子
	else
      q=&HT[q->rchild];//编码为1找又孩子
   }//for
 }//while
}//else
    fclose(fp2);
    fclose(fp3);
}//decompress
main(int argc,char *argv[])
{
	FILE *fp1,*fp2,*fp3;
	if(argc==1||(argc==2&&!strcmp(argv[1],"help")))
	{
		printf("文件压缩：Myzip.exe -c 要压缩的文件名 压缩后的文件名\n");
		printf("文件解压：Myzip.exe -d 压缩文件名 解压后的文件名\n");
	}
	else if(argc==4)
   {
	if(!strcmp(argv[1],"-c"))//当命令参数为"-c"时对文件进行压缩
	{
	  if((fp1=fopen(argv[2],"rb"))==NULL)
	    {
		 printf("cannot open file\n");
		 exit(0);
	     }
	   if((fp2=fopen(argv[3],"wb"))==NULL)
	  {
		printf("cannot open file\n");
		exit(0);
	   }
     compress(fp1,fp2);//执行文件压缩
	}//if
   else if(!strcmp(argv[1],"-d"))//当命令参数为"-d"时对文件进行解压
     {
     if((fp2=fopen(argv[2],"rb"))==NULL)
	   {
		printf("cannot open file\n");
		exit(0);
	   }
     if((fp3=fopen(argv[3],"wb"))==NULL)
	   {
		printf("cannot open file\n");
		exit(0);
	   }
      decompress(fp2,fp3);//执行文件解压
	}
   else
	   printf("命令行参数错误，可输入:Myzip.exe help寻求帮助\n");
  }
 else
	 printf("命令行参数错误，可输入:Myzip.exe help寻求帮助\n");
 system("pause");
}//main