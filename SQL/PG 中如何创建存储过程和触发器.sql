/*	
 PG ����δ����洢���̺ʹ����� ������ 2012-06-15 16:16:33 
*/
--��Ա���ϱ�
create table users
(          
   yhm varchar(20) not null,
   primary key(yhm)  
) ;

--��¼users���ж��ټ�¼
CREATE TABLE users_recordnum
(
   recordnum integer not null default 0
) ;

INSERT INTO  users_recordnum VALUES(default);

--�����û�procedure
CREATE OR REPLACE FUNCTION users_insert(a_yhm VARCHAR) RETURNS TEXT AS
$$
BEGIN
     PERFORM 1 FROM users WHERE yhm=a_yhm;
     IF FOUND THEN
         RETURN '�û��Ѿ�����';
     ELSE
         INSERT INTO users(yhm) VALUES(a_yhm); 
     END IF; 
     RETURN '';
END;
$$
LANGUAGE PLPGSQL;

--ɾ���û�procedure

CREATE OR REPLACE FUNCTION users_delete(a_yhm VARCHAR) RETURNS TEXT AS
$$
BEGIN  
     DELETE FROM users WHERE yhm=a_yhm;
     IF FOUND THEN
         RETURN 'ɾ���ɹ�';
     ELSE
         RETURN '�û�������';
     END IF; 
END;
$$
LANGUAGE PLPGSQL;


--����һ��users������¼��trigger�������ɹ�������1
CREATE OR REPLACE FUNCTION "public"."users_insert_trigerr_func" () RETURNS trigger AS
$body$
BEGIN
    UPDATE users_recordnum SET recordnum=recordnum+1; 
    RETURN NEW;
END;
$body$
LANGUAGE 'plpgsql'
;

CREATE TRIGGER "users_insert_trigerr" AFTER INSERT 
ON "public"."users" FOR EACH ROW 
EXECUTE PROCEDURE "public"."users_insert_trigerr_func"();

--����һ��usersɾ����¼��trigger��ɾ���ɹ�������1
CREATE OR REPLACE FUNCTION "public"."users_delete_trigerr_func" () RETURNS trigger AS
$body$
BEGIN
    UPDATE users_recordnum SET recordnum=recordnum-1; 
    RETURN OLD;
END;
$body$
LANGUAGE 'plpgsql'
;

CREATE TRIGGER "users_delete_trigerr" AFTER DELETE 
ON "public"."users" FOR EACH ROW 
EXECUTE PROCEDURE "public"."users_delete_trigerr_func"();

--������¼

SELECT users_insert('��ΰƽ'); 
SELECT users_insert('���������'); 
SELECT users_delete('����');
SELECT users_delete('����2012');
SELECT users_delete('����2012');

--ɾ����¼
SELECT users_delete('����2012');
SELECT users_delete('pgsql');