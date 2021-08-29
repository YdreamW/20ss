const User = require('./User') 
const mysql = require('mysql')

class DataBase {
    constructor(host,user,password,database,server) {
        this.conn = mysql.createConnection({
            host: host,
            user: user,
            password: password,
            database: database
        })
        this.conn.connect((err) => {
            if (err) {
                console.log("\x1b[31m%s\x1b[0m",'[错误] 数据库连线失败，请检查配置');
                console.log("\x1b[31m%s\x1b[0m",'[错误] 错误内容：' + err.message);
                console.log("\x1b[31m%s\x1b[0m",'[错误] 服务器初始化失败，即将关闭 ...');
                server.close();
            } else {
                console.log("\x1b[32m%s\x1b[0m",'[信息] 数据库连线成功。');
            }
        })
    }
}

module.exports = DataBase;