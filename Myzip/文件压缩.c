FILE *yasuo(FILE *fp1,FILE *fp2)
{
	HuffmanTree HT,q;HuffmanCode HC;
	int i,a[256],b[256],ch,num,j,s,k,t;
	char filename1[20],filename2[20],*p;
    if((fp1=fopen(filename1,"rb"))==NULL)
	  {
		printf("cannot open file\n");
		exit(0);
	  }
	if((fp2=fopen(filename2,"wb"))==NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	for(i=0;i<256;i++)
		a[i]=0;
	num=0;
	while(1)
	{
		ch=fgetc(fp1);
		if(feof(fp1)) break;
		  a[ch]++;
		num++;//统计文件中字符的个数
	}
	j=0;
	for(i=0;i<256;i++)
		if(a[i]!=0)
		{
			b[j]=a[i];
			j++;
		}
	if(j==0)
	{
		printf("该文件为空文件，不需压缩。\n");
		system("pause");
	    exit(0);
	}
	else 
	{
		fprintf(fp2,"%d ",num);
		fprintf(fp2,"%d",j);
		for(i=0;i<256;i++)
		   if(a[i]!=0)
             fprintf(fp2,"%c",i);
		for(i=0;i<256;i++)
		 if(a[i]!=0)
           fprintf(fp2,"%d ",a[i]);
	if(j>1)
	{
    HuffmanCoding(&HT,&HC,b,j);//数组b[]存放j个字符的权值(>0),构造赫夫曼树HT，并求出j个字符的赫夫曼编码HC
   /* printf("%d  %d  %d  \n",HT[2*j-1].lchild,HT[2*j-1].rchild,HT[2*j-1].weight);*/
	 j=s=0;
	 rewind(fp1);//使位置指针重新返回到文件的开头
     while(1)
	 {
		ch=fgetc(fp1);
		if(feof(fp1)) break;
		k=position(ch,a);//字符ch是文件中第k个频率不为0的字符（按ASCII码顺序）
		for(p=HC[k];*p!='\0';p++)
		{
			t=*p-'0';
			s=s<<1;
			s=s+t;
			j++;
			if(j==8)//当编码数为8时将其作为一个字节存入到压缩文件中
				{
					fputc(s,fp2);
					s=0;
					j=0;
			    }//if
		}//for
      }//while
   if(j<8)
	  {
		  s=s<<(8-j);
		 fputc(s,fp2);
      }//将不足8位的编码用0补齐
	 }//if
   fclose(fp1);
   fclose(fp2);
   }//else
   return(fp2);
}//yasuo