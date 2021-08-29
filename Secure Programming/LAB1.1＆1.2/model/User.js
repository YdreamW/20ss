class User {
    constructor(conn) {
        this.conn = conn;
    }
    findById(usr_name) {
        const sql = "SELECT * FROM `users` WHERE `usr_name`='" + usr_name + "';";
        return new Promise((resolve, reject) => {
            this.conn.query(sql, (err, results) => {
                if (err) {
                    reject(err);
                } else {
                    resolve(results[0]);
                }
            })
        })
    }
    checkPwd(usr_name, pwd) {
        const sql = "SELECT * FROM `users` WHERE `usr_name`='" + usr_name + "';";
        return new Promise((resolve, reject) => {
            this.conn.query(sql, (err, results) => {
                if (err) {
                    reject(err);
                } else {
                    const {
                        pwd: Upwd
                    } = results[0];
                    if (pwd !== Upwd) {
                        resolve(false);
                    } else {
                        resolve(true);
                    }
                }
            })
        })
    }
    insert(usr_name, pwd, Tname, student_num) {
        const sql = "INSERT INTO users (usr_name,pwd,Tname,student_num) VALUES ('" + usr_name + "','" + pwd + "','" + Tname + "','" + student_num + "');";
        return new Promise((resolve, reject) => {
            this.conn.query(sql, (err, results) => {
                if (err) {
                    reject(err);
                } else {
                    resolve(true);
                }
            })
        })
    }
}

module.exports = User;