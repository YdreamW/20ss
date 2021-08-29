$(document).ready(function () {
    $('#loginForm').submit(function (e) {
        e.preventDefault();
        let keepLogin = 'no';
        if ($('#keeplogin').is(':checked')) {
            keepLogin = 'on';
        }
        $.ajax({
            type: "POST",
            url: 'login',
            data: {
                user: $("#id").val(),
                pwd: md5($('#pwd').val()),
                keepLogin: keepLogin
            },
            success: (res) => {
                const {
                    code,
                    msg,
                    data
                } = res;
                if (!code) {
                    window.document.write(res);
                } else {
                    alert(msg);
                }

            }
        });
    });
});

$(document).ready(function () {
    $('#registerForm').submit(function (e) {
        e.preventDefault();
        if ($('#reg_pwd').val() != $('#reg_checkpwd').val()) {
            alert("两次密码输入不一致！");
            return;
        }
        $.ajax({
            type: "POST",
            url: 'register',
            data: {
                usr_name: $('#reg_id').val(),
                pwd: md5($('#reg_pwd').val()),
                Tname: $('#reg_name').val(),
                student_num: $('#reg_schoolnumber').val()
            },
            success: (res) => {
                const {
                    code,
                    msg
                } = res;
                if (!code) {
                    window.document.write(res);
                } else {
                    alert(msg);
                }

            }
        });
    });
});