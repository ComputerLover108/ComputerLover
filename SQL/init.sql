/*
	ɾ�����ݿ�
*/
drop database if exists "HLD-terminal" ; --�����ñ����ˣ��������ݽ���ʧ����
-- delete from pg_databases where datname='HLD-terminal'; ��Ч��һ�����PostgreSQL ר�У�
/*
	ɾ���û�
*/
drop user if exists "recover" ; --ɾ�������û�����ȷ����
-- delete from pg_roles where rolname='recover' ;
/*
��ʾ:  You need an unconditional ON DELETE DO INSTEAD rule or an INSTEAD OF DELETE trigger.
��û�о����ף�
*/
drop user if exists "operator"; --ɾ���������ݿ���û�����ȷ����
drop user if exists "leader","leader1","leader2"; --ɾ����ѯ�û����쵼�����ܲ鿴���ݿ⣬��ȷ����
drop user if exists "cz","cz1","cz2","cz3","cz4","cz5"; --ɾ������û������˲�������ˣ���ȷ����
/*
	�����ȱ����û�recover����������Ϊ3,���Ҵ������� 
*/
create user recover  replication encrypted password '2971';
alter user recover  connection limit 3 ;
/*
	������ѯ�û�������Ҫ���룡
*/
create user leader ; --�쵼����Ҫ���룡
/*
	�������������ɫ
*/
create user "operator"  createdb createrole encrypted password '5302491' ;
create user "cz1"  encrypted password '5302469' ;
create user "cz2"  encrypted password '5302469' ;
create user "cz3"  encrypted password '5302469' ;
create user "cz4"  encrypted password '5302469' ;
create user "cz5"  encrypted password '5302469' ;

/*
	�������ݿ�
*/
create	database	"HLD-terminal" encoding 'UTF8' ;
alter	database	"HLD-terminal" owner to "operator" ;
alter	database	"HLD-terminal" connection limit 64 ;
/*
	ɾ��ȫ������
*/
drop table if exists 
	"�������", 
	"����",
	"����",
	"����",
	"���",
	"����",
	"���Ϸ���",
	"������Ϣ",
	"��Ա��Ϣ"
	;
	
/*
	�������ֱ���
*/
create table if not exists "���Ϸ���" (
	"ID"		smallint,
	"Ӣ������"	varchar(16),
	"����"		varchar(16),
	"���"		varchar(16)
);
alter table "���Ϸ���" owner to "operator";
/*
*/
create table if not exists "�������" (
	"����"		date,
	"����"		varchar(16),
	"��λ"		varchar(8),
	"�����"	int,
	"�����"	int,
	"�����"	int
);
alter table "�������" owner to "operator";
/*
*/
create table if not exists "����ͳ��" (
	"����"		date,
	"����"		varchar(16),
	"��λ"		varchar(8),
	"�ղ�"		numeric(10,4),
	"���"		varchar(8),
	"״̬"		varchar(8),	
	"��ע"		varchar(64)
);
alter table "����ͳ��" owner to "operator";
/*
*/
create table if not exists "������Ϣ" (
	"ʱ��"		timestamp,
	"����"		varchar(16),
	"��Ŀ"		varchar(8),
	"��λ"		varchar(8),
	"����"		numeric(10,4)
);
alter table "������Ϣ" owner to "operator";
/*
*/
create table if not exists "��Ա��Ϣ" (
	"����"		varchar(8),
	"�Ա�"		varchar(2),
	"ְ��"		varchar(16),
	"ѧ��"		varchar(8),
	"ְ��"		varchar(16),
	"��ϵ��ַ"	varchar(32),
	"��ϵ�绰"	varchar(16),
	"��ϵ�绰1"	varchar(16),
	"QQ��"		varchar(16),
	"�����ʼ�"	varchar(16)
);
alter table "��Ա��Ϣ" owner to "operator";
/*
*/

