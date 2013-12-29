void jieya(FILE *fp2,FILE *fp3)
{
   int i,n,l,ch,d[8];
   HuffmanTree HT,q;HuffmanCode HC;
   fscanf(fp2,"%d",&number);
   fscanf(fp2,"%d",&n);
   for(i=1;i<=n;i++)
      fscanf(fp2,"%c",&f[i]);
   for(i=0;i<n;i++)
	  fscanf(fp2,"%d",&w[i]);
   if(n==1)
	  for(i=0;i<w[0];i++)
		fputc(f[1],fp3);
   else
   {
    HuffmanCoding(&HT,&HC,w,n);
   q=&HT[2*n-1];
   l=0;
   ch=fgetc(fp2);
   while(1)
	{
		ch=fgetc(fp2);
		if(feof(fp2)) break;
		i=7;
		while(i!=-1)
		{
			c=ch%2;
            ch=ch/2;
			d[i]=c;
			i--;
		}
		/*for(i=0;i<8;i++)
		   printf("%d ",d[i]);
		printf("\n");*/
		for(i=0;i<8;i++)
			{
			  if(q->lchild==0&&q->rchild==0)
				for(j=1;j<=n;j++)
					if(q==&HT[j])
					{
					   if(l<number)
						{
						   fprintf(fp3,"%c",f[j]);
						   l++;
						}
					   q=&HT[2*n-1];break;
				     }//if
			if(d[i]==0)
		      q=&HT[q->lchild];
			else
			  q=&HT[q->rchild];
		   }//for
    }//while
}//else
    fclose(fp2);
    fclose(fp3);
}//jieya