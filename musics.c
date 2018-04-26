#define uint unsigned int
#define uchar unsigned char

uchar code jingo[] = {
0x15,0x15,0x23,0x23,0x22,0x22,0x21,0x21,
0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
0x15,0x15,0x23,0x23,0x22,0x22,0x21,0x21,
0x16,0x16,0x16,0x16,0x16,0x16,0x16,0x16,
0x16,0x16,0x24,0x24,0x23,0x23,0x22,0x22,
0x17,0x17,0x17,0x17,0x17,0x17,0x15,0x25,
0x25,0x25,0x25,0x24,0x24,0x22,0x22,0x23,
0x23,0x23,0x23,0x21,0x21,0x15,0x15,0x15,
0x15,0x23,0x23,0x22,0x22,0x21,0x21,0x15,
0x15,0x15,0x15,0x15,0x15,0x15,0x15,0x15,
0x23,0x23,0x22,0x22,0x21,0x21,0x16,0x16,
0x16,0x16,0x16,0x16,0x16,0x15,0x15,0x24,
0x24,0x23,0x23,0x22,0x22,0x25,0x25,0x25,
0x25,0x25,0x00,0x00,0x00,0x00,0x00,0x00
};

uchar code tongyi[] ={    //音乐代码，歌曲为《同一首歌》，格式为: 音符, 节拍, 音符, 节拍,    
0x21,0x21,0x22,0x22,0x23,0x23,0x15,0x15,0x15,0x15,0x21,0x21,
0x22,0x22,0x23,0x23,0x23,0x24,0x23,0x23,0x21,0x21,0x22,0x22,
0x22,0x22,0x21,0x21,0x16,0x16,0x21,0x21,0x21,0x21,0x21,0x21,
0x21,0x21,0x15,0x15,0x15,0x15,0x21,0x21,0x22,0x22,0x23,0x23,
0x23,0x24,0x25,0x25,0x21,0x21,0x24,0x24,0x24,0x23,0x25,0x25,
0x22,0x23,0x23,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x23,0x23,
0x23,0x23,0x25,0x25,0x31,0x31,0x27,0x27,0x27,0x26,0x26,0x26,
0x26,0x26,0x25,0x25,0x25,0x26,0x27,0x27,0x26,0x25,0x23,0x23,
0x23,0x23,0x23,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

uchar code nevforg[] = {
0x27,0x27,0x27,0x27,0x25,0x25,0x27,0x27,
0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,
0x25,0x25,0x17,0x17,0x21,0x21,0x25,0x25,
0x24,0x24,0x24,0x24,0x24,0x24,0x23,0x23,
0x23,0x22,0x22,0x23,0x23,0x26,0x26,0x27,
0x27,0x31,0x31,0x27,0x27,0x27,0x27,0x26,
0x26,0x26,0x26,0x26,0x26,0x25,0x25,0x25,
0x25,0x23,0x23,0x31,0x27,0x31,0x27,0x31,
0x31,0x23,0x25,0x25,0x25,0x23,0x23,0x23,
0x23,0x23,0x23,0x23,0x23,0x23,
0x00,0x00,0x00,0x00
};

uchar code quzi[] ={	  //此数组数据为各个音符在定时器中的重装值，第一列是高位，第二列是低位
0xf8,0x8c,	  //低八度，低1
0xf9,0x5b,	  
0xfa,0x15,	  //低3
0xfa,0x67,
0xfb,0x04,	  //低5
0xfb,0x90,
0xfc,0x0c,	  //低7	
0xfc,0x44,	  //中央C调
0xfc,0xac,	  //中2
0xfd,0x09,
0xfd,0x34,	  //中4
0xfd,0x82,
0xfd,0xc8,	  //中6
0xfe,0x06,
0xfe,0x22,	  //高八度，高1	
0xfe,0x56,
0xfe,0x6e,	  //高3
0xfe,0x9a,
0xfe,0xc1,	  //高5
0xfe,0xe4,
0xff,0x03	  //高7
};

uchar quyin(uchar tem)
{
	uchar qudiao,jp,weizhi;		  //定义曲调，音符和位置
	qudiao=tem/16;				  //高4位是曲调值
	jp=tem%16;					  //低4位是音符
	if(qudiao==1)				  //当曲调值为1时，即是低八度，低八度在quzi数组中基址为0
		qudiao=0;
	else if(qudiao==2)			  //当曲调值为2时，即是中八度，中八度在quzi数组中基址为14
		qudiao=14;
	else if(qudiao==3)			  //当曲调值为3时，即是高八度，高八度在quzi数组中，基址为28
		qudiao=28;
	weizhi=qudiao+(jp-1)*2;		  //通过基址加上音符作为偏移量，即可定位此音符在quzi数组中的位置
	return weizhi;				  //返回这一个位置值
}