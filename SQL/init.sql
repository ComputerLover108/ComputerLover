/*
	删除数据库
*/
drop database if exists "HLD-terminal" ; --你做好备份了！所有数据将丢失！？
-- delete from pg_databases where datname='HLD-terminal'; 等效上一个命令，PostgreSQL 专有！
/*
	删除用户
*/
drop user if exists "recover" ; --删除备份用户，你确定？
-- delete from pg_roles where rolname='recover' ;
/*
提示:  You need an unconditional ON DELETE DO INSTEAD rule or an INSTEAD OF DELETE trigger.
还没研究明白！
*/
drop user if exists "operator"; --删除建立数据库的用户，你确定？
drop user if exists "leader","leader1","leader2"; --删除查询用户，领导将不能查看数据库，你确定？
drop user if exists "cz","cz1","cz2","cz3","cz4","cz5"; --删除填表用户，工人不能填表了，你确定？
/*
	建立热备份用户recover，连接限制为3,并且带有密码 
*/
create user recover  replication encrypted password '2971';
alter user recover  connection limit 3 ;
/*
	建立查询用户，不需要密码！
*/
create user leader ; --领导不需要密码！
/*
	建立带有密码角色
*/
create user "operator"  createdb createrole encrypted password '5302491' ;
create user "cz1"  encrypted password '5302469' ;
create user "cz2"  encrypted password '5302469' ;
create user "cz3"  encrypted password '5302469' ;
create user "cz4"  encrypted password '5302469' ;
create user "cz5"  encrypted password '5302469' ;

/*
	建立数据库
*/
create	database	"HLD-terminal" encoding 'UTF8' ;
alter	database	"HLD-terminal" owner to "operator" ;
alter	database	"HLD-terminal" connection limit 64 ;
/*
	删除全部报表
*/
drop table if exists 
	"配产任务", 
	"生产",
	"消耗",
	"接收",
	"库存",
	"销售",
	"物料分类",
	"生产信息",
	"人员信息"
	;
	
/*
	建立各种报表
*/
create table if not exists "物料分类" (
	"ID"		smallint,
	"英文名称"	varchar(16),
	"名称"		varchar(16),
	"类别"		varchar(16)
);
alter table "物料分类" owner to "operator";
/*
*/
create table if not exists "配产任务" (
	"日期"		date,
	"名称"		varchar(16),
	"单位"		varchar(8),
	"年配产"	int,
	"月配产"	int,
	"日配产"	int
);
alter table "配产任务" owner to "operator";
/*
*/
create table if not exists "生产统计" (
	"日期"		date,
	"名称"		varchar(16),
	"单位"		varchar(8),
	"日产"		numeric(10,4),
	"类别"		varchar(8),
	"状态"		varchar(8),	
	"备注"		varchar(64)
);
alter table "生产统计" owner to "operator";
/*
*/
create table if not exists "生产信息" (
	"时间"		timestamp,
	"名称"		varchar(16),
	"项目"		varchar(8),
	"单位"		varchar(8),
	"数量"		numeric(10,4)
);
alter table "生产信息" owner to "operator";
/*
*/
create table if not exists "人员信息" (
	"姓名"		varchar(8),
	"性别"		varchar(2),
	"职务"		varchar(16),
	"学历"		varchar(8),
	"职称"		varchar(16),
	"联系地址"	varchar(32),
	"联系电话"	varchar(16),
	"联系电话1"	varchar(16),
	"QQ号"		varchar(16),
	"电子邮件"	varchar(16)
);
alter table "人员信息" owner to "operator";
/*
*/

