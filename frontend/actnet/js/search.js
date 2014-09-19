/**
 * Created by Rodolphe on 2014/7/7.
 */

$(document).ready(function () {
    $("#search").submit(function() {
        act = $("#input-box").val();
        console.log(act);
        if (act !== "") {
            window.location = "/activity/" + encodeURIComponent(act);
            return false;
        } else {
            return false;
        }
    });
});