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
		num++;//ͳ���ļ����ַ��ĸ���
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
		printf("���ļ�Ϊ���ļ�������ѹ����\n");
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
    HuffmanCoding(&HT,&HC,b,j);//����b[]���j���ַ���Ȩֵ(>0),����շ�����HT�������j���ַ��ĺշ�������HC
   /* printf("%d  %d  %d  \n",HT[2*j-1].lchild,HT[2*j-1].rchild,HT[2*j-1].weight);*/
	 j=s=0;
	 rewind(fp1);//ʹλ��ָ�����·��ص��ļ��Ŀ�ͷ
     while(1)
	 {
		ch=fgetc(fp1);
		if(feof(fp1)) break;
		k=position(ch,a);//�ַ�ch���ļ��е�k��Ƶ�ʲ�Ϊ0���ַ�����ASCII��˳��
		for(p=HC[k];*p!='\0';p++)
		{
			t=*p-'0';
			s=s<<1;
			s=s+t;
			j++;
			if(j==8)//��������Ϊ8ʱ������Ϊһ���ֽڴ��뵽ѹ���ļ���
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
      }//������8λ�ı�����0����
	 }//if
   fclose(fp1);
   fclose(fp2);
   }//else
   return(fp2);
}//yasuo