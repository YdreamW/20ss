class ChannelList {
    constructor(conn) {
        this.conn = conn;
    }
    findAll() {
        const sql = "SELECT * FROM `channel` ;";
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
    findByName(channel_name){
        const sql = "SELECT * FROM `channel` WHERE `channel_name`='" + channel_name + "';";
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
    findById(id){
        const sql = "SELECT * FROM `channel` WHERE `id`='" + id + "';";
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
    addChanel(channel_name){
        const sql = "INSERT INTO channel (channel_name) VALUES ('" + channel_name +  "');";
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

module.exports = ChannelList;