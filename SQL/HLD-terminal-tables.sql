create table "配产任务" (
	"日期"		date,
	"名称"		varchar(16),
	"单位"		varchar(8),
	"年配产"	int,
	"月配产"	int,
	"日配产"	int
);
/*
*/
create table "生产" (
	"日期"		date,
	"名称"		varchar(16),
	"单位"		varchar(8),
	"日产"		numeric(10,4),
	"类别"		varchar(8),	
	"备注"		varchar(64)
);
/*
*/
create table "消耗" (
	"日期"		date,
	"名称"		varchar(16),
	"单位"		varchar(8),
	"数量"		numeric(10,4),
	"类别"		varchar(8),	
	"备注"		varchar(64)
);
create table "接收" (
	"日期"		date,
	"名称"		varchar(16),
	"单位"		varchar(8),
	"数量"		numeric(10,4),
	"类别"		varchar(8),	
	"备注"		varchar(64)
);
/*
*/
create table "库存" (
	"日期"		date,
	"名称"		varchar(16),
	"单位"		varchar(8),
	"数量"		numeric(10,4),
	"类别"		varchar(8),
	"备注"		varchar(64)
);
/*
*/
create table "销售" (
	"日期"		date,
	"名称"		varchar(16),
	"单位"		varchar(8),
	"数量"		numeric(10,4),
	"类别"		varchar(8),
	"备注"		varchar(64)
);
/*
*/
create table "物料分类" (
	"ID"	smallint,
	"类别"	varchar(16)
);
/*
*/
create table "设备生产信息" (
	"时间"		timestamp,
	"名称"		varchar(16),
	"项目"		varchar(8),
	"单位"		varchar(8)
	"数量"		numeric(10,4)
);
/*
*/
create table "人员信息" (
	"姓名"		varchar(8),
	"性别"		varchar(2),
	"职务"		varchar(16),
	"学历"		varchar(8),
	"职称"		varchar(16),
	"联系地址"	varchar(32),
	"联系电话"	varchar(16),
	"联系电话"	varchar(16),
	"QQ号"		varchar(16),
	"电子邮件"	varchar(16)
);
