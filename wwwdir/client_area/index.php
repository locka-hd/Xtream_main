<?php

require "../init.php";
session_start();
if (!(!empty($_SESSION["client_loggedin"]) && $_SESSION["client_loggedin"] === true && !empty($_SESSION["cl_data"]))) {
    if (!(!empty(a78Bf8d35765Be2408C50712CE7a43aD::$request["username"]) && !empty(a78Bf8D35765bE2408c50712CE7a43aD::$request["password"]))) {
        goto Edca3ffe9250f93804ca6930c52ae31e;
    }
    $f566700a43ee8e1f0412fe10fbdf03df->query("SELECT * FROM `users` WHERE `username` = '%s' AND `password` = '%s' AND (`exp_date` >= " . time() . " OR `exp_date` is null) LIMIT 1", A78bF8D35765bE2408c50712ce7a43aD::$request["username"], a78Bf8D35765BE2408C50712Ce7a43AD::$request["password"]);
    if ($f566700a43ee8e1f0412fe10fbdf03df->getRowCount() > 0) {
        $_SESSION["client_loggedin"] == true;
        $_SESSION["cl_data"] = $f566700a43ee8e1f0412fe10fbdf03df->F1eD191D78470660EdFf4A007696bC1f();
        header("Location: live.php");
        die;
    }
    $A311af351a57a1d9580a9fe53b473019 = "<div id=\"wrong_user_information\">*** " . $A22f04f5efe932bdb34320e92642825a["wrong_info_client"] . " ***</div>";
    Edca3ffe9250f93804ca6930c52ae31e:
    if (empty($_GET["action"])) {
        goto Ebb02f8298a9003b768842c44f9d2a97;
    }
    switch ($_GET["action"]) {
        case "logout":
            session_destroy();
            header("Location: index.php");
            die;
    }
    A343c01625b4df947736524e5fc743da:
    Ebb02f8298a9003b768842c44f9d2a97:
?>
    <!DOCTYPE html>
    <html>

    <head>
        <meta http-equiv="content-type" content="text/html; charset=UTF-8">
        <title>Client_Login</title>
        <link rel="stylesheet" type="text/css" href="css/login.css">
    </head>

    <body>
        <div style="height:136px; width:100%; background-image:url(images/back_line_login.png); margin-top:22%;"></div>

        <!--   Center Arrow and Logo Code   -->
        <center>
            <div style="width:378px; height:494px; background-image:url(images/login_card.png); margin-top:-315px;">



                <!--   Form Code   -->

                <form id="login" method="post" action="index.php">
                    <fieldset id="inputs_login">
                        <input id="username" placeholder="username" name="username" autofocus required type="text">
                        </br> </br>
                        <input id="password" name="password" placeholder="password" required type="password">
                    </fieldset>
                    <fieldset id="actions">
                        <input id="submit" value="" type="submit">
                    </fieldset>
                </form>
            </div>
            <?php
            if (empty($A311af351a57a1d9580a9fe53b473019)) {
                goto d104952481ca2416341adc63c555e363;
            }
            echo "<font color=\"red\">" . $A311af351a57a1d9580a9fe53b473019 . "</font>";
            d104952481ca2416341adc63c555e363:
            ?>
        </center>
    </body>

    </html>
<?php
    // [PHPDeobfuscator] Implied script end
    return;
}
header("Location: live.php");
die;
