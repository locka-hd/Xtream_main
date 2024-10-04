function randomNumber(a, e) { return Math.random() * (e - a) + a } function randomBar(a, e) { var t = randomNumber(.95 * e, 1.05 * e), r = randomNumber(.95 * t, 1.05 * t); return { t: a.valueOf(), y: r } } !function (l) { "use strict"; var a = function () { this.$body = l("body"), this.charts = [] }; a.prototype.respChart = function (e, t, r, o) { var n = e.get(0).getContext("2d"), i = l(e).parent(); return function () { var a; switch (e.attr("width", l(i).width()), t) { case "Line": a = new Chart(n, { type: "line", data: r, options: o }); break; case "Doughnut": a = new Chart(n, { type: "doughnut", data: r, options: o }); break; case "Pie": a = new Chart(n, { type: "pie", data: r, options: o }); break; case "Bar": a = new Chart(n, { type: "bar", data: r, options: o }); break; case "Radar": a = new Chart(n, { type: "radar", data: r, options: o }); break; case "PolarArea": a = new Chart(n, { data: r, type: "polarArea", options: o }) }return a }() }, a.prototype.initCharts = function () { var a = []; if (0 < l("#line-chart-example").length) { a.push(this.respChart(l("#line-chart-example"), "Line", { labels: ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"], datasets: [{ label: "Current Week", backgroundColor: "rgba(86, 194, 214, 0.3)", borderColor: "#56c2d6", data: [32, 42, 42, 62, 52, 75, 62] }, { label: "Previous Week", fill: !0, backgroundColor: "transparent", borderColor: "#f0643b", borderDash: [5, 5], data: [42, 58, 66, 93, 82, 105, 92] }] }, { maintainAspectRatio: !1, legend: { display: !1 }, tooltips: { intersect: !1 }, hover: { intersect: !0 }, plugins: { filler: { propagate: !1 } }, scales: { xAxes: [{ reverse: !0, gridLines: { color: "rgba(0,0,0,0.05)" } }], yAxes: [{ ticks: { stepSize: 20 }, display: !0, borderDash: [5, 5], gridLines: { color: "rgba(0,0,0,0)", fontColor: "#fff" } }] } })) } if (0 < l("#bar-chart-example").length) { a.push(this.respChart(l("#bar-chart-example"), "Bar", { labels: ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"], datasets: [{ label: "Sales Analytics", backgroundColor: "#f0643b", borderColor: "#f0643b", hoverBackgroundColor: "#f0643b", hoverBorderColor: "#f0643b", data: [65, 59, 80, 81, 56, 89, 40, 32, 65, 59, 80, 81] }, { label: "Dollar Rate", backgroundColor: "#e3eaef", borderColor: "#e3eaef", hoverBackgroundColor: "#e3eaef", hoverBorderColor: "#e3eaef", data: [89, 40, 32, 65, 59, 80, 81, 56, 89, 40, 65, 59] }] }, { maintainAspectRatio: !1, legend: { display: !1 }, scales: { yAxes: [{ gridLines: { display: !1 }, stacked: !1, ticks: { stepSize: 20 } }], xAxes: [{ barPercentage: .7, categoryPercentage: .5, stacked: !1, gridLines: { color: "rgba(0,0,0,0.01)" } }] } })) } if (0 < l("#pie-chart-example").length) { a.push(this.respChart(l("#pie-chart-example"), "Pie", { labels: ["Direct", "Affilliate", "Sponsored", "E-mail"], datasets: [{ data: [300, 135, 48, 154], backgroundColor: ["#4a81d4", "#f672a7", "#e3eaef", "#f0643b"], borderColor: "transparent" }] }, { maintainAspectRatio: !1, legend: { display: !1 } })) } if (0 < l("#donut-chart-example").length) { a.push(this.respChart(l("#donut-chart-example"), "Doughnut", { labels: ["Direct", "Affilliate", "Sponsored"], datasets: [{ data: [128, 78, 48], backgroundColor: ["#ebeff2", "#56c2d6", "#f0643b"], borderColor: "transparent", borderWidth: "3" }] }, { maintainAspectRatio: !1, cutoutPercentage: 60, legend: { display: !1 } })) } if (0 < l("#polar-chart-example").length) { a.push(this.respChart(l("#polar-chart-example"), "PolarArea", { labels: ["Direct", "Affilliate", "Sponsored", "E-mail"], datasets: [{ data: [251, 135, 48, 154], backgroundColor: ["#4a81d4", "#ebeff2", "#56c2d6", "#f0643b"], borderColor: "transparent" }] })) } if (0 < l("#radar-chart-example").length) { a.push(this.respChart(l("#radar-chart-example"), "Radar", { labels: ["Eating", "Drinking", "Sleeping", "Designing", "Coding", "Cycling", "Running"], datasets: [{ label: "Desktops", backgroundColor: "rgba(86, 194, 214, 0.3)", borderColor: "#56c2d6", pointBackgroundColor: "#56c2d6", pointBorderColor: "#fff", pointHoverBackgroundColor: "#fff", pointHoverBorderColor: "#56c2d6", data: [65, 59, 90, 81, 56, 55, 40] }, { label: "Tablets", backgroundColor: "rgba(240, 100, 59,0.2)", borderColor: "#f0643b", pointBackgroundColor: "#f0643b", pointBorderColor: "#fff", pointHoverBackgroundColor: "#fff", pointHoverBorderColor: "#f0643b", data: [28, 48, 40, 19, 96, 27, 100] }] }, { maintainAspectRatio: !1 })) } return a }, a.prototype.init = function () { var e = this; Chart.defaults.global.defaultFontFamily = '-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,Oxygen-Sans,Ubuntu,Cantarell,"Helvetica Neue",sans-serif', e.charts = this.initCharts(), l(window).on("resize", function (a) { l.each(e.charts, function (a, e) { try { e.destroy() } catch (a) { } }), e.charts = e.initCharts() }) }, l.ChartJs = new a, l.ChartJs.Constructor = a }(window.jQuery), function (a) { "use strict"; window.jQuery.ChartJs.init() }(); for (var dateFormat = "MMMM DD YYYY", date = moment("April 01 2017", dateFormat), data = [randomBar(date, 30)], labels = [date]; data.length < 24;)(date = date.clone().add(1, "d")).isoWeekday() <= 5 && (data.push(randomBar(date, data[data.length - 1].y)), labels.push(date)); var ctx = document.getElementById("financial-report").getContext("2d"); ctx.canvas.width = 1e3; var cfg = { type: "bar", data: { labels: labels, datasets: [{ label: "CHRT - Chart.js Corporation", data: data, type: "line", pointRadius: 0, fill: !(ctx.canvas.height = 300), lineTension: 0, borderWidth: 2 }] }, options: { scales: { xAxes: [{ type: "time", distribution: "series", ticks: { source: "labels" } }], yAxes: [{ scaleLabel: { display: !0, labelString: "Closing price ($)" } }] } } }, chart = new Chart(ctx, cfg); document.getElementById("update").addEventListener("click", function () { var a = document.getElementById("type").value; chart.config.data.datasets[0].type = a, chart.update() });