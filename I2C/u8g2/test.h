#ifndef __TEST_H
#define __TEST_H
 
#include "main.h"
#include "u8g2.h"
#include "stdio.h"

void testDrawProcess(u8g2_t *u8g2);
void testShowFont(u8g2_t *u8g2);
void testDrawFrame(u8g2_t *u8g2);
void testDrawRBox(u8g2_t *u8g2);
void testDrawCircle(u8g2_t *u8g2);
void testDrawFilledEllipse(u8g2_t *u8g2);
void testDrawMulti(u8g2_t *u8g2);
void testDrawXBM(u8g2_t *u8g2);
 
void u8g2DrawTest(u8g2_t *u8g2);

/*��*/
static const unsigned char  zuo[] ={
0x40,0x00,0x40,0x00,0x40,0x00,0xFF,0x7F,0x20,0x00,0x20,0x00,0x20,0x00,0x10,0x00,0xF0,0x1F,0x08,0x01,0x08,0x01,0x04,0x01,0x02,0x01,0x01,0x01,0xFC,0x7F,0x00,0x00};

/*��*/
static const unsigned char zai[] ={
0x10,0x00,0xD0,0x1F,0x10,0x10,0x08,0x08,0x08,0x04,0x0C,0x02,0x0C,0x02,0xEA,0x7F,0x09,0x02,0x08,0x02,0x08,0x02,0x08,0x02,0x08,0x02,0x08,0x02,0x88,0x02,0x08,0x01};

	
static const unsigned char wen[] =	
{0x00,0x00,0xC4,0x1F,0x48,0x10,0x48,0x10,0xC1,0x1F,0x42,0x10,0x42,0x10,0xC8,0x1F,0x08,0x00,0xE4,0x3F,0x27,0x25,0x24,0x25,0x24,0x25,0x24,0x25,0xF4,0x7F,0x00,0x00};/*"��",0*/

static const unsigned char du[] =
{0x80,0x00,0x00,0x01,0xFC,0x7F,0x44,0x04,0x44,0x04,0xFC,0x3F,0x44,0x04,0x44,0x04,0xC4,0x07,0x04,0x00,0xF4,0x0F,0x24,0x08,0x42,0x04,0x82,0x03,0x61,0x0C,0x1C,0x70};/*"��",1*/

static const unsigned char shi[] =
{0x00,0x00,0xE4,0x1F,0x28,0x10,0x28,0x10,0xE1,0x1F,0x22,0x10,0x22,0x10,0xE8,0x1F,0x88,0x04,0x84,0x04,0x97,0x24,0xA4,0x14,0xC4,0x0C,0x84,0x04,0xF4,0x7F,0x00,0x00};/*"ʪ",2*/

static const unsigned char dai[] =	
{0x10,0x02,0x10,0x02,0x08,0x02,0xC4,0x3F,0x12,0x02,0x10,0x02,0xE8,0x7F,0x0C,0x08,0x0A,0x08,0xE9,0x7F,0x08,0x08,0x48,0x08,0x88,0x08,0x88,0x08,0x08,0x0A,0x08,0x04};/*"��",4*/

static const unsigned char jian[] =	
{0x08,0x02,0x08,0x02,0x08,0x05,0x08,0x05,0xBF,0x08,0x48,0x10,0xAC,0x6F,0x1C,0x00,0x2A,0x11,0x0A,0x12,0x49,0x12,0x88,0x0A,0x88,0x08,0x08,0x04,0xE8,0x7F,0x08,0x00};/*"��",5*/

static const unsigned char ce[] =	
{0x00,0x20,0xE4,0x23,0x28,0x22,0x28,0x2A,0xA1,0x2A,0xA2,0x2A,0xA2,0x2A,0xA8,0x2A,0xA8,0x2A,0xA4,0x2A,0xA7,0x2A,0x84,0x20,0x44,0x21,0x44,0x22,0x24,0x28,0x10,0x10};/*"��",6*/
	
	
	
static const unsigned char  shen[] ={
0x40,0x00,0x20,0x00,0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x08,0x08,0xF8,0x4F,0x08,0x28,0x08,0x18,0xFE,0x0F,0x00,0x0A,0x00,0x09,0xC0,0x08,0x38,0x08,0x07,0x0A,0x00,0x04};/*"��",0*/
/* (16 X 16 , ���� )*/

static const unsigned char  wu[] ={
0x00,0x00,0xFC,0x0F,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0xFE,0x3F,0x20,0x01,0x20,0x01,0x20,0x01,0x10,0x01,0x10,0x01,0x08,0x21,0x04,0x21,0x02,0x3E,0x01,0x00};/*"��",1*/
/* (16 X 16 , ���� )*/

static const unsigned char  cai[] ={
0x80,0x00,0xE0,0x21,0x1E,0x20,0x10,0x11,0x22,0x09,0xA4,0x44,0x04,0x40,0x20,0x20,0xFE,0x11,0x30,0x08,0x68,0x44,0xA8,0x40,0x24,0x21,0x22,0x10,0x21,0x08,0x20,0x06};/*"��",2*/
/* (16 X 16 , ���� )*/

static const unsigned char  feng[] ={
0x00,0x00,0xFC,0x1F,0x04,0x10,0x04,0x10,0xF4,0x13,0x04,0x12,0x14,0x12,0x24,0x11,0x44,0x11,0x84,0x10,0x44,0x11,0x24,0x52,0x14,0x52,0x02,0x50,0x02,0x60,0x01,0x40};/*"��",3*/
/* (16 X 16 , ���� )*/

	
static const unsigned char  shaung[] ={
0x00,0x00,0x00,0x00,0xBF,0x3F,0x20,0x21,0x22,0x21,0x22,0x21,0x14,0x11,0x14,0x11,0x08,0x0A,0x08,0x0A,0x14,0x04,0x14,0x04,0x22,0x0A,0x22,0x11,0x81,0x20,0x40,0x40};/*"˫",4*/
/* (16 X 16 , ���� )*/
	
static const unsigned char  fei[] ={
0x00,0x00,0xFF,0x03,0x00,0x02,0x00,0x22,0x00,0x12,0x00,0x0A,0x00,0x06,0x00,0x0A,0x00,0x12,0x00,0x22,0x00,0x04,0x00,0x04,0x00,0x48,0x00,0x50,0x00,0x60,0x00,0x40};/*"��",5*/
/* (16 X 16 , ���� )*/
	
static const unsigned char  yi[] ={
0x7E,0x3F,0x44,0x22,0x58,0x2C,0x46,0x23,0x40,0x20,0xFC,0x1F,0x84,0x10,0xFC,0x1F,0x84,0x10,0xFC,0x1F,0x20,0x02,0xFC,0x1F,0x20,0x02,0xFF,0x7F,0x10,0x04,0x08,0x08};/*"��",6*/
/* (16 X 16 , ���� )*/



#endif
