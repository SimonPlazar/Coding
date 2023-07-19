$(document).ready(function () {
    $("#reset").click(function () {
        $.get("ponastavi.php", function () {
            $.get("potopi.php");
            $("td").removeClass("hit").removeClass("miss");
            $("p").html("Število poskusov: 0");
        })
    })

    function createTable() {
        for (var i = 0; i < 10; ++i) {
            var tr = document.createElement("tr");
            $("table").append(tr);
            for (var j = 0; j < 10; ++j) {
                tr.append(document.createElement("td"));
            }
        }
    }

    createTable();

    $("td").click(function (e) {
        if (!$(e.currentTarget).hasClass('hit') && !$(e.currentTarget).hasClass('miss')) {
            $.get("getSessionInfo.php", function (data) {
                var poskusi = parseInt(data);
                $("p").html("Število poskusov: " + poskusi);
            });

            var x = this.cellIndex + 1;
            var y = $(this).parent().index() + 1;

            $.get("preveri.php?x=" + x + "&y=" + y, function (data) {

                var odgovor = JSON.parse(data);

                if (odgovor.isHit) {
                    $(e.currentTarget).addClass('hit');
                } else {
                    $(e.currentTarget).addClass('miss');
                }
                if (odgovor.konec) {
                    alert("Konec! Št. poskusov: " + odgovor.poskusi);
                    $("table").off("click", "td");
                }
            });
        }
    })
});