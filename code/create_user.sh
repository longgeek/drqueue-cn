#!/bin/bash

read -p "输入需要创建的用户名字: " USERNAME
cat /etc/passwd | grep ^$USERNAME: > /dev/null

if [ "$?" -eq 0 ]; then
    echo '用户已存在'
    exit
fi

read -p "输入 $USERNAME 用户的密码: " USERPASSWORD

LDAP_CN=$(hostname | awk -F. '{print $1}')
LDAP_DN=$(hostname | awk -F. '{print $2"."$3}')
useradd $USERNAME; echo $USERPASSWORD | passwd --stdin $USERNAME
cat /etc/passwd | grep ^$USERNAME: > /tmp/passwd
cat /etc/group | grep ^$USERNAME: > /tmp/group
perl /usr/share/migrationtools/migrate_passwd.pl /tmp/passwd  /tmp/passwd.ldif
perl /usr/share/migrationtools/migrate_group.pl /tmp/group  /tmp/group.ldif
ldapadd -D "cn=$LDAP_CN,dc=$LDAP_DN" -w password -x -f /tmp/passwd.ldif
ldapadd -D "cn=$LDAP_CN,dc=$LDAP_DN" -w password -x -f /tmp/group.ldif
source /etc/profile
USERSTATUS=$(cat $OLDPWD/environment.rb | grep "ENV\['USER_STATUS'\] ||=" | awk -F'"' '{print $2}')
sed -i "s/$USERSTATUS/$USERSTATUS,$USERNAME/g" $OLDPWD/environment.rb

USERQUOTA=$(cat $OLDPWD/environment.rb | grep "ENV\['USER_QUOTA'\] ||=" | awk -F'"' '{print $2}')
sed -i "s/$USERQUOTA/$USERQUOTA,50/g" $OLDPWD/environment.rb

USERPRIO=$(cat $OLDPWD/environment.rb | grep "ENV\['USER_PRIO'\] ||=" | awk -F'"' '{print $2}')
sed -i "s/$USERPRIO/$USERPRIO,500/g" $OLDPWD/environment.rb

DBNAME=$(cat $OLDPWD/database.yml | grep -A 4 production: | grep database | awk '{print $NF}')
DBUSER=$(cat $OLDPWD/database.yml | grep -A 4 production: | grep username | awk '{print $NF}')
DBPASS=$(cat $OLDPWD/database.yml | grep -A 4 production: | grep password | awk '{print $NF}')
mysql -u $DBUSER -p$DBPASS -e "insert into $DBNAME.profiles(name,email,avatar,ldap_account,status,accepted) values('$USERNAME Account','$USERNAME@$(hostname | awk -F. '{print $2"."$3}')','NULL','$USERNAME','$USERNAME','0');"
/etc/init.d/httpd reload
