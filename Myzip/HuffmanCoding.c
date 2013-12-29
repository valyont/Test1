void Select(HuffmanTree HT,int i,int *s1,int *s2)
{
	int j,k;
	k=HT[i].weight;
	for(j=1;j<=i;j++)
		if(HT[j].weight<=k&&HT[j].parent==0)
			{
				k=HT[j].weight;
				*s1=j;
		     }
	if(*s1==i)
		k=HT[i-1].weight;
	else
		k=HT[i].weight;
	 HT[*s1].parent++;
	 for(j=1;j<=i;j++)
		if(HT[j].weight<=k&&HT[j].parent==0)
			{
				k=HT[j].weight;
				*s2=j;
		     }
}
void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n)
{
	int m,i,start,f,c,s1,s2;
	char *cd;
	HuffmanTree p;
	m=2*n-1;
	*HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
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
		Select(*HT,i-1,&s1,&s2);
		printf("************************%d  %d  %d\n",s1,s2,i);
		(*HT)[s1].parent=i;
		(*HT)[s2].parent=i;
		(*HT)[i].lchild=s1;
		(*HT)[i].rchild=s2;
		(*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
	}
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	cd=(char *)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;i++)
	{
		start=n-1;
		for(c=i,f=(*HT)[i].parent;f!=0;c=f,f=(*HT)[f].parent)
			if((*HT)[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
		(*HC)[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy((*HC)[i],&cd[start]);
	}
	free(cd);
}//HuffmanCoding