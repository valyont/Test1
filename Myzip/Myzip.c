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
	//��HT[1..i]��ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
{
	int j,k;
	k=HT[i].weight;
	for(j=1;j<=i;j++)
		if(HT[j].weight<=k&&HT[j].parent==0)
			{
				k=HT[j].weight;
				*s1=j;
		     }//��Ȩֵ��С�Ľ��
    HT[*s1].parent++;
	for(j=i;j>=1;j--)
		if(HT[j].parent==0)
			{
			   k=HT[j].weight;
			   break;
		    }//��һ��parentΪ0�Ľ��
	 for(j=1;j<=i;j++)
		if(HT[j].weight<=k&&HT[j].parent==0)
			{
				k=HT[j].weight;
				*s2=j;
		     }//��Ȩֵ��С����һ���
}//Select
void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n)
	//w���n���ַ���Ȩֵ(>0),����շ�����HT�������n���ַ��ĺշ�������HC
{
	int m,i,start,f,c,s1,s2;
	char *cd;
	HuffmanTree p;
	m=2*n-1;//mΪ�շ����������ܸ�����nΪҶ�ӽ����
	*HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//0�ŵ�Ԫδ��
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
		Select(*HT,i-1,&s1,&s2);//��HT[1..i-1]��ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
		(*HT)[s1].parent=i;
		(*HT)[s2].parent=i;
		(*HT)[i].lchild=s1;
		(*HT)[i].rchild=s2;
		(*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
	}//���շ�����
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char *));//����n���ַ������ͷָ������
	cd=(char *)malloc(n*sizeof(char));//���������Ĺ����ռ�
	cd[n-1]='\0';//���������
	for(i=1;i<=n;i++)
	{
		start=n-1;//���������λ��
		for(c=i,f=(*HT)[i].parent;f!=0;c=f,f=(*HT)[f].parent)//��Ҷ�ӵ������������
			if((*HT)[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
		(*HC)[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy((*HC)[i],&cd[start]);//��cd���Ʊ��뵽HC
	}
	free(cd);//�ͷŹ����ռ�
}//HuffmanCoding
void compress(FILE *fp1,FILE *fp2)
	//����fp1Ϊ�ļ�ָ����ļ�����ѹ����ѹ������ļ�Ϊfp2
{
	HuffmanTree HT;HuffmanCode HC;
	int i,j,n,s,k,t,w[256],weight[256],ch,num;
	char *p;
	for(i=0;i<256;i++)
		w[i]=0;//��ÿ���ַ���Ƶ�ʳ�ʼ��
	num=0;//�ļ������ַ�����ʼ��Ϊ0
	while(1)
	{
		ch=fgetc(fp1);
		if(feof(fp1)) break;
		w[ch]++;//ͳ���ļ���ÿ���ַ���Ƶ��
		num++;//ͳ���ļ����ַ��ĸ���
	}
	n=0;
	for(i=0;i<256;i++)
		if(w[i]!=0)
		{
		  weight[n]=w[i];
		  n++;
		}//���Ƶ�ʲ�Ϊ0���ַ��ĸ�����Ϊn��������Ӧ��Ƶ�ʴ�������weight[]��
   if(n==0)
	{
	printf("���ļ�Ϊ���ļ�������ѹ����\n");
	system("pause");
	exit(0);
	}//���ļ���ѹ����ֱ���˳�
	else 
	{
	 fprintf(fp2,"%d ",num);
	 fprintf(fp2,"%d",n);
	 for(i=0;i<256;i++)
	   if(w[i]!=0)
        fprintf(fp2,"%c",i);
	 for(i=0;i<256;i++)
	   if(w[i]!=0)
         fprintf(fp2,"%d ",w[i]);//�����ǽ��ļ����ܳ��ȡ��ַ����ࡢ�ַ����ַ�Ƶ�ʴ���ѹ���ļ�
  if(n>1)//���ַ�����>1��ʱ�򣬹���շ���������ѹ��
 {
    HuffmanCoding(&HT,&HC,weight,n);//����weight[]���n���ַ���Ȩֵ(>0),����շ�����HT�������n���ַ��ĺշ�������HC
	 i=s=0;
	 rewind(fp1);//ʹλ��ָ�����·��ص��ļ��Ŀ�ͷ
     while(1)
   {
	 ch=fgetc(fp1);
	 if(feof(fp1)) break;
	 k=0;
	 for(j=0;j<=ch;j++)
		if(w[j]!=0)
			k++;//�ַ�ch���ļ��е�k��Ƶ�ʲ�Ϊ0���ַ�����ASCII��˳��
	 for(p=HC[k];*p!='\0';p++)
	 {
	   t=*p-'0';
	   s=s<<1;
	   s=s+t;
	   i++;
	   if(i==8)//��������Ϊ8ʱ������Ϊһ���ֽڴ��뵽ѹ���ļ���
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
  }//������8λ�ı�����0����
 }//if(n>1)
  fclose(fp1);
  fclose(fp2);
 }//else
}//compress
void decompress(FILE *fp2,FILE *fp3)
{
   int i,j,n,number,ch,num,c,bit[8],w[256];
   char f[257];//�������������0�ŵ�Ԫ���ñ���һ��
   HuffmanTree HT,q;HuffmanCode HC;
   fscanf(fp2,"%d",&num);//�����ļ��ܵ��ַ�����
   fscanf(fp2,"%d",&n);//�����ļ��������ַ�������
   for(i=1;i<=n;i++)
      fscanf(fp2,"%c",&f[i]);//���ļ��е��ַ���������f[]
   for(i=0;i<n;i++)
	  fscanf(fp2,"%d",&w[i]);//ÿ���ַ���Ȩ�ش�������w[]
   if(n==1)
	  for(i=0;i<w[0];i++)
		fputc(f[1],fp3);//���ļ�ֻ��һ���ַ�ʱ��ֱ�����
   else
   {
   HuffmanCoding(&HT,&HC,w,n);//w���n���ַ���Ȩֵ(>0),����շ�����HT�������n���ַ��ĺշ�������HC
   q=&HT[2*n-1];//qָ������
   number=0;
   ch=fgetc(fp2);//��ȡһ����������Ŀո�
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
	}//���ַ�ת���ɶ�Ӧ�ı���
	for(i=0;i<8;i++)
	{
	  if(q->lchild==0&&q->rchild==0)//qΪҶ�ӽ��
	   for(j=1;j<=n;j++)
		if(q==&HT[j])
		{
		if(number<num)//��������ַ���С��ԭ�ļ������ַ���ʱ����������
	   {
		 fprintf(fp3,"%c",f[j]);
		 number++;
	   }
	    q=&HT[2*n-1];break;//���½�qָ����������´μ���Ѱ��
		}//if
	if(bit[i]==0)
	  q=&HT[q->lchild];//����Ϊ0������
	else
      q=&HT[q->rchild];//����Ϊ1���ֺ���
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
		printf("�ļ�ѹ����Myzip.exe -c Ҫѹ�����ļ��� ѹ������ļ���\n");
		printf("�ļ���ѹ��Myzip.exe -d ѹ���ļ��� ��ѹ����ļ���\n");
	}
	else if(argc==4)
   {
	if(!strcmp(argv[1],"-c"))//���������Ϊ"-c"ʱ���ļ�����ѹ��
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
     compress(fp1,fp2);//ִ���ļ�ѹ��
	}//if
   else if(!strcmp(argv[1],"-d"))//���������Ϊ"-d"ʱ���ļ����н�ѹ
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
      decompress(fp2,fp3);//ִ���ļ���ѹ
	}
   else
	   printf("�����в������󣬿�����:Myzip.exe helpѰ�����\n");
  }
 else
	 printf("�����в������󣬿�����:Myzip.exe helpѰ�����\n");
 system("pause");
}//main