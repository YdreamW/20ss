const User = require("../model/User");
const DataBase = require("../model/DataBase");
const ChannelList = require("../model/ChannelList");
const Message = require("../model/Message");

const controller = {};

//Create object of the database
controller.dataBase = new DataBase("localhost", "root", "123", "sp_lab1", controller.server);
controller.conn = controller.dataBase.conn;

controller.login = async (req, res) => {
    const { body } = req;
    const thisUser = new User(controller.conn);
    const usr = await thisUser.findById(body.user);
    if (!usr) {
        res.json({
            code: 2,
            msg: "没有该用户，请先注册",
        });
        res.end();
    } else {
        const flag = thisUser.checkPwd(body.user, body.pwd);
        if (!flag) {
            res.json({
                code: 3,
                msg: "密码错误",
            });
            res.end();
        } else {
            const { usr_name, pwd, Tname, student_num } = usr;
            if (body.keepLogin === "on") {
                req.session.account = "True";
            }
            req.session.channel_name = "default channel";
            req.session.usr_name = usr_name;
            req.session.pwd = pwd;
            req.session.Tname = Tname;
            req.session.student_num = student_num;
            res.render("../views/chatRoom", {
                usr_name,
                pwd,
                Tname,
                student_num,
            });
        }
    }
};
controller.register = async (req, res) => {
    const { body } = req;
    const { usr_name, pwd, Tname, student_num } = body;
    const thisUser = new User(controller.conn);
    const usr = await thisUser.findById(usr_name);
    if (usr) {
        res.json({
            code: 2,
            msg: "该用户名已被使用",
        });
        res.end();
    } else {
        const flag = await thisUser.insert(usr_name, pwd, Tname, student_num);
        if (flag) {
            req.session.usr_name = usr_name;
            req.session.channel_name = "default channel";
            req.session.pwd = pwd;
            req.session.Tname = Tname;
            req.session.student_num = student_num;
            res.render("../views/chatRoom", {
                usr_name,
                pwd,
                Tname,
                student_num,
            });
        }
    }
};

controller.getChannelList = async (req, res) => {
    const thisChannelList = new ChannelList(controller.conn);
    const results = await thisChannelList.findAll();
    let htmlStr = "";
    const thisC = req.session.channel_name;
    for (const i of results) {
        if (i.channel_name !== thisC) {
            htmlStr +=
                "<tr><td><h3 id='" +
                i.id +
                "' onclick=\"changechannel('" +
                i.id +
                '\')" style="margin: 6px; font-size: 20px; cursor: pointer;color:gray;">' +
                i.channel_name +
                "</h3></td></tr>";
        } else {
            htmlStr +=
                "<tr><td><h3 id='" +
                i.id +
                "' onclick=\"changechannel('" +
                i.id +
                '\')" style="margin: 6px; font-size: 20px; cursor: pointer;color:brown;">' +
                i.channel_name +
                "</h3></td></tr>";
        }
    }
    res.json({
        code: 0,
        msg: "successful",
        htmlStr,
    });
    res.end();
};

controller.addChannel = async (req, res) => {
    const { body } = req;
    const { channel_name } = body;
    if (req.session && req.session.usr_name) {
        const thisChannelList = new ChannelList(controller.conn);
        const result = await thisChannelList.findByName(channel_name);
        if (result) {
            res.json({
                code: 2,
                msg: "该频道名已被使用",
            });
            res.end();
        } else {
            const flag = await thisChannelList.addChanel(channel_name);
            if (flag) {
                res.json({
                    code: 0,
                    msg: "successful",
                });
                res.end();
            } else {
                res.json({
                    code: 3,
                    msg: "未知错误",
                });
                res.end();
            }
        }
    } else {
        res.json({
            code: 1,
            msg: "权限错误",
        });
        res.end();
    }
};

controller.addMsg = async (req, res) => {
    const { body, session } = req;
    const { msg } = body;
    if (session && session.usr_name) {
        const { channel_name, usr_name } = session;
        if (!channel_name) {
            res.json({
                code: 3,
                msg: "没有频道",
            });
            res.end();
        } else {
            const message = new Message(controller.conn);
            const t = Date.now();
            const time = t.toString();
            const flag = await message.addMsg(channel_name, usr_name, msg, time);
            if (flag) {
                res.json({
                    code: 0,
                    msg: "successful",
                });
                res.end();
            } else {
                res.json({
                    code: 3,
                    msg: "未知错误",
                });
                res.end();
            }
        }
    } else {
        res.json({
            code: 1,
            msg: "权限错误",
        });
        res.end();
    }
};

controller.getChat = async (req, res) => {
    const { body, session } = req;
    if (session && session.channel_name) {
        const { channel_name } = session;
        const message = new Message(controller.conn);
        const results = await message.findAll(channel_name);
        let htmlStr = "";
        for (const i of results) {
            htmlStr +=
                '<div style="margin-left: 30px"><p style="padding:5px 15px 5px 15px;display: inline-block; background-color:white; border-radius:20px; max-width: 60%"><a style="font-size:6px; color:gray">' +
                i.usr_name +
                " - " +
                i.time +
                " </a> <br> " +
                i.msg +
                "</p></div>";
        }
        res.json({
            code: 0,
            msg: "successful",
            htmlStr,
        });
        res.end();
    } else {
        res.json({
            code: 1,
            msg: "没有选择频道",
        });
        res.end();
    }
};

controller.changeChannel = async (req, res) => {
    const { body, session } = req;
    const { id } = body;
    if (session && session.usr_name) {
        const thisChannelList = new ChannelList(controller.conn);
        const result = await thisChannelList.findById(id);
        session.channel_name = result.channel_name;
        res.json({
            code: 0,
            msg: "successful",
            channel_name: result.channel_name,
        });
        res.end();
    } else {
        res.json({
            code: 1,
            msg: "权限错误",
        });
        res.end();
    }
};

controller.logout = (req, res) => {
    req.session.destroy();
    res.render("../views/index");
};

module.exports = controller;
