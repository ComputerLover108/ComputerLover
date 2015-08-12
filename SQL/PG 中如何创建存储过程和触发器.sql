/*	
 PG 中如何创建存储过程和触发器 发表于 2012-06-15 16:16:33 
*/
--会员资料表
create table users
(          
   yhm varchar(20) not null,
   primary key(yhm)  
) ;

--记录users表有多少记录
CREATE TABLE users_recordnum
(
   recordnum integer not null default 0
) ;

INSERT INTO  users_recordnum VALUES(default);

--增加用户procedure
CREATE OR REPLACE FUNCTION users_insert(a_yhm VARCHAR) RETURNS TEXT AS
$$
BEGIN
     PERFORM 1 FROM users WHERE yhm=a_yhm;
     IF FOUND THEN
         RETURN '用户已经存在';
     ELSE
         INSERT INTO users(yhm) VALUES(a_yhm); 
     END IF; 
     RETURN '';
END;
$$
LANGUAGE PLPGSQL;

--删除用户procedure

CREATE OR REPLACE FUNCTION users_delete(a_yhm VARCHAR) RETURNS TEXT AS
$$
BEGIN  
     DELETE FROM users WHERE yhm=a_yhm;
     IF FOUND THEN
         RETURN '删除成功';
     ELSE
         RETURN '用户不存在';
     END IF; 
END;
$$
LANGUAGE PLPGSQL;


--增加一个users新增记录的trigger，新增成功人数加1
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

--增加一个users删除记录的trigger，删除成功人数减1
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

--新增记录

SELECT users_insert('何伟平'); 
SELECT users_insert('有理想的猪'); 
SELECT users_delete('阿弟');
SELECT users_delete('阿弟2012');
SELECT users_delete('阿弟2012');

--删除记录
SELECT users_delete('阿弟2012');
SELECT users_delete('pgsql');