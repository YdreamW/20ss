update_channellist = () => {
    $.ajax({
        type: "POST",
        url: "getchannellist",
        success: function (data) {
            const { code, msg, htmlStr } = data;
            //console.log(data);
            if (code === 0) {
                $("#channelist").html(htmlStr);
            }
        },
    });
};

function add_channel() {
    var newname = prompt("Please enter new channel name", "name of new channel");
    $.ajax({
        type: "POST",
        url: "addchannel",
        data: {
            channel_name: newname,
        },
        success: (data) => {
            const { code, msg } = data;
            if (code !== 0) {
                alert(msg);
            }
        },
    });
}

function add_msg() {
    $.ajax({
        type: "POST",
        url: "addmsg",
        data: {
            msg: $("#msg").val(),
        },
        success: (data) => {
            const { code, msg } = data;
            if (code !== 0) {
                alert(msg);
            }
        },
    });
}

update_chat = () => {
    $.ajax({
        type: "POST",
        url: "getchat",
        success: function (data) {
            const { code, msg, htmlStr } = data;
            //console.log(data);
            $("#chatdiv").html(htmlStr);
        },
    });
};
function changechannel(channel_id) {
    $.ajax({
        type: "POST",
        url: "changeChannel",
        data: {
            id: channel_id,
        },
        success: function (data) {
            const { code, msg, channel_name } = data;
            //console.log(data);
            $("#channel_title").html("<h2>" + channel_name + "</h2>");
        },
    });
}
function logout() {
    $.ajax({
        type: "POST",
        url: "logout",
        success: (res) => {
            window.document.body.innerHTML='';
            window.document.write(res);
        },
    });
}
