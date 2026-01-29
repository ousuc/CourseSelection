#!/bin/bash
set -e  # 遇错立即退出，防止无效执行
# 全局配置（与你的libpq连接字符串完全一致，无需修改）
NEW_USER="ousuc"        # 要创建的数据库用户
NEW_PASS="A"            # 用户密码
NEW_DB="school_system"  # 要创建的数据库
ROOT_USER="postgres"    # PostgreSQL超级管理员（默认postgres）
SQL_FILE="init_school_data.sql" # 关联的SQL初始化文件

# 检查psql是否安装
if ! command -v psql &> /dev/null; then
    echo "【错误】未检测到psql客户端，请先安装PostgreSQL客户端工具！"
    exit 1
fi

# 检查SQL文件是否存在
if [ ! -f "$SQL_FILE" ]; then
    echo "【错误】未找到SQL初始化文件 $SQL_FILE，请确保与本脚本放在同一目录！"
    exit 1
fi

# 检查PostgreSQL服务是否启动
if ! systemctl is-active --quiet postgresql; then
    echo "【提示】PostgreSQL服务未启动，正在尝试自动启动..."
    sudo systemctl start postgresql
    sleep 2  # 等待服务启动完成
fi

echo -e "==================== 开始初始化数据库环境 ====================\n"

# 步骤1：以postgres超级管理员执行——独立命令+兼容排序规则（最终修复）
echo "【1/3】创建用户 $NEW_USER + 数据库 $NEW_DB ..."
# 1. 删除原有用户（独立执行，无事务）
sudo -u postgres psql -c "DROP ROLE IF EXISTS $NEW_USER;"
# 2. 创建新用户（独立执行，无事务）
sudo -u postgres psql -c "CREATE ROLE $NEW_USER WITH LOGIN PASSWORD '$NEW_PASS' NOSUPERUSER NOCREATEDB NOCREATEROLE;"
# 3. 删除原有数据库（独立执行，无事务）
sudo -u postgres psql -c "DROP DATABASE IF EXISTS $NEW_DB;"
# 4. 创建新数据库——核心修复：指定TEMPLATE template0 + 统一C.UTF-8排序规则
sudo -u postgres psql -c "CREATE DATABASE $NEW_DB WITH OWNER = $NEW_USER ENCODING = 'UTF8' LC_COLLATE = 'C.UTF-8' LC_CTYPE = 'C.UTF-8' TEMPLATE template0;"
# 5. 赋予数据库基础权限
sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE $NEW_DB TO $NEW_USER;"

# 步骤2：以新用户ousuc执行——批量执行SQL文件（创建表+插入测试数据+验证）
echo -e "\n【2/3】创建表结构并插入测试数据 ..."
export PGPASSWORD="$NEW_PASS"
psql -U "$NEW_USER" -d "$NEW_DB" -f "$SQL_FILE"

# 步骤3：赋权序列权限（适配Grades表SERIAL自增主键，避免libpq插入报错）
echo -e "\n【3/3】赋予序列操作权限（适配自增主键） ..."
sudo -u postgres psql -d "$NEW_DB" -c "GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO $NEW_USER;"
sudo -u postgres psql -d "$NEW_DB" -c "ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT ALL PRIVILEGES ON TABLES TO $NEW_USER;"

# 清理环境变量+执行完成提示
unset PGPASSWORD
echo -e "\n====================================================="
echo "✅ 数据库环境初始化完成！libpq可直接使用以下配置："
echo "static string configuration = \"host=localhost dbname=school_system user=ousuc password=A port=5432\";"
echo "====================================================="
echo "💡 说明：C语言/libpq需要指定host/port走TCP/IP，本地Shell脚本适配套接字无需指定"

