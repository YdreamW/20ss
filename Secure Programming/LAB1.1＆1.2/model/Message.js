class Message {
    constructor(conn) {
        this.conn = conn;
    }
    findAll(channel_name) {
        const sql = "SELECT * FROM `messages` WHERE `channel_name`='" + channel_name + "';";
        return new Promise((resolve, reject) => {
            this.conn.query(sql, (err, results) => {
                if (err) {
                    reject(err);
                } else {
                    resolve(results);
                }
            })
        })
    }
    addMsg(channel_name,usr_name,msg,time){
        const sql = "INSERT INTO messages (channel_name,time,msg,usr_name) VALUES ('" + channel_name +  "', now() , '"+msg+"' , '"+usr_name+"' );";
        return new Promise((resolve, reject) => {
            this.conn.query(sql, (err, results) => {
                if (err) {
                    reject(err);
                } else {
                    resolve(results);
                }
            })
        })
    }
    
}



module.exports = Message;