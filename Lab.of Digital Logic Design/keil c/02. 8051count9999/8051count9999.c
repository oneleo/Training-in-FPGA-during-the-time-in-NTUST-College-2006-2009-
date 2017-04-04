#include "reg51.h"
short seg[4]={0},scan_num=0,scan=0;/*seg�Ψ��x�s�U�ӤC�q��ܾ����ƭȡAscan�O���y���w�ΡAscan_num�O���wscan���B�ӫG�A��seg���Ʀr�~�G*/
unsigned short seg_scan[4]={0x0e,0x0d,0x0b,0x07};/*��ܭ��ӤC�q��ܾ����*/
unsigned short seg_num[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};/*�C�q��ܾ�0~F����ܤ覡*/
void delay(int del)
{
  long d;
  for(d=0;d<del;d++)
  {
    ; 
  } 
}
void T0_int(void)interrupt 1  /*���_�{�ǡA�Ҧ���1*/
{
  TH0=(65536-10000)/256;      /*�]�w�U�����_����ɶ��A�ɶ��@��A�A�׶i�J�����_�{��*/
  TL0=(65536-10000)%256;      /*�p���~�i���_���C�q�֥[�ʧ@�C*/
  seg[0]++;                   /*�Ӧ�Ʋ֥[1�C*/
  if(seg[0]==10)              /*�p�G�Ӧ�Ƭ�9+1�������A���Ӧ���k0�A���Q��Ʋ֥[1�A*/
  {
    seg[0]=0;
    seg[1]++;
    if(seg[1]==10)            /*�p�G�Q��Ƭ�9+1�������A���Q����k0�A���ʦ�Ʋ֥[1�C*/
    {
      seg[1]=0;
      seg[2]++;
      if(seg[2]==10)          /*�p�G�ʦ�Ƭ�9+1�������A���ʦ���k0�A���d��Ʋ֥[1�C*/
      {
        seg[2]=0;
        seg[3]++;
        if(seg[3]==10)        /*�p�G�d��Ƭ�9+1�������A���d��Ƭ��k0�C*/
        { 
          seg[3]=0;
        }
      }
    }
  }
}
int main(void)
{
  IE=0x82;                /*�]�w�p�ɤ��_*/
  TMOD=0x01;              /*�]�w���_�Ҧ�*/
  TH0=(65536-10000)/256;  /*�]�w���_����ɶ��A�]�w������A�Y�q���ɲִ�A���0�ɶi�J���_�{��*/
  TL0=(65536-10000)%256;  /*�]�w���_����ɶ��A�����G�]65536��x�^�At��x(us)*/
  TR0=1;                  /*�Ұʭp�ɾ��A��AT89S51�p�ɾ��Ұ�*/
  while(1)                /*�i�J���y�{��*/
  {
    delay(64);  	      /*���y����A�Y���y�L�֡A�|�ݤ�����ܵ��G�C*/
    P0=seg_scan[scan];    /*�]�wAT89S51��P0.0�BP0.1�BP0.2�BP0.3����n�����ӤC�q��ܾ��o���A�]���|�ӤC�q��ܾ���abcdefgh���}�P���@�ݡA�ҥH�n�Υt�|������u�M�w���ӧO�C�q��ܾ����ݪ��T���L�ӮɡA�n���ӤC�q��ܾ��o���C*/
    P1=seg_num[seg[scan]];/*�]�wAT89S51��P1.0�BP1.1�BP1.2�BP1.3�BP1.4�BP1.5�BP1.6�BP1.7���O���J�C�q��ܾ���abcdefgh�A�]���|�ӤC�q��ܾ�����ƽu���ۦP�A�ҥH�ȤC���N�i�����A�A�y�ѧֳt���y�A�ײ��L�k��O�����p�U�A�F����ت��C*/
    if(seg[1]!=0)         /*�Ǫ��n�D�Y����ƭȬ�0���ܡA�h������C�q��ܾ���ܡC*/
    { 
      scan_num=1;         /*�P�O�O�_����ơA�Y�S����ƪ��ܡA���L���y�C*/
    } 
    if(seg[2]!=0)
    {
      scan_num=2;
    } 
    if(seg[3]!=0)
    {
      scan_num=3;
    }
    scan++;
    if(scan>scan_num)
    { 
    scan=0;
    } 
  }
}