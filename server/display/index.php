<html>

<head>
    <title>Magic Mirror Group D</title>
    <meta name="google" content="notranslate" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <link rel="icon" href="data:;base64,iVBORw0KGgo=">
    <link rel="stylesheet" type="text/css" href="css/main.css">
    <link rel="stylesheet" type="text/css" href="fonts/roboto.css">
    <script src="js/clock.js"></script>
    <script src="js/jquery.js"></script>
    <script src="js/load.js"> </script>
</head>
<body>
    <div class="region fullscreen below">
        <div class="container"></div>
    </div>
    <div class="region top bar">
        <!-- TOP - LEFT area -->
        <div class="region top left">
            <div class="container"></div>
            <div id="day"></div>
            <div id="clock"></div>
            <div id="calendar"></div>
            <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>
            <script src="js/calendar.js"></script>
            <script>
                $('#calendar').datepicker({
                    inline: false,
                    firstDay: 1,
                    showOtherMonths: true,
                    dayNamesMin: ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat']
                });
            </script>
        </div>
        <!-- TOP - RIGHT area -->
        <div class="region top right">
            <div class="container"></div>     
            <table id="weather" width="450" height="350" border='0'>
                <tr rowspan=3 width="300">
                    <td align=center colspan=2 ><img id='weather_icon' src='img/wait.png'></td>
                    <td align=center colspan=2 ><img src="img/thermometer2.png"></td>
					<td align=center colspan=2 id='dht_temperature'>00</td>
                    <td align=center colspan=2 id='elm'>°C</td>
                </tr>
                <tr rowspan=1>
                    <td align=center colspan=1><img src="img/pressure.png"></td>
                    <td align=center colspan=2 id="elm">Pressure</td>
                    <td align=center colspan=1 id="elm">:</td>
                    <td align=center colspan=1 id="bmp_pressure">00</td>
                    <td align=center colspan=3 id="unit">Pa</td>
                </tr>
                <tr rowspan=1>
                    <td align=center colspan=1><img src="img/humidity.png"></td>
                    <td align=center colspan=2 id="elm">Humidity</td>
                    <td align=center colspan=1 id="elm">:</td>
                    <td align=center colspan=1 id="dht_humidity">00</td>
                    <td align=center colspan=3 id="unit">%</td>
                </tr>
				<tr rowspan=1>
                    <td align=center colspan=1><img src="img/thermometer.png"></td>
                    <td align=center colspan=2 id="elm">Temperature</td>
                    <td align=center colspan=1 id="elm">:</td>
                    <td align=center colspan=1 id="bmp_temperature">00</td>
                    <td align=center colspan=3 id="unit">°C</td>
                </tr>
                <tr rowspan=1>
                    <td align=center colspan=1><img src="img/altitude.png"></td>
                    <td align=center colspan=2 id="elm">Altitude</td>
                    <td align=center colspan=1 id="elm">:</td>
                    <td align=center colspan=1 id="bmp_altitude">00</td>
                    <td align=center colspan=3 id="unit">m</td>
                </tr>
				<tr rowspan=1>
                    <td align=center colspan=1><img src="img/lux.png"></td>
                    <td align=center colspan=2 id="elm">Lux</td>
                    <td align=center colspan=1 id="elm">:</td>
                    <td align=center colspan=1 id="tsl_lux">00</td>
                    <td align=center colspan=3 id="unit">lx</td>
                </tr>
                <tr rowspan=1>
                    <td align=center colspan=1><img src="img/lux.png"></td>
                    <td align=center colspan=2 id="elm">Full Luminosity</td>
                    <td align=center colspan=1 id="elm">:</td>
                    <td align=center colspan=1 id="tsl_full_luminosity">00</td>
                    <td align=center colspan=3 id="unit"></td>
                </tr>
                <tr rowspan=1>
                    <td align=center colspan=1><img src="img/lux.png"></td>
                    <td align=center colspan=2 id="elm">Ir luminosity</td>
                    <td align=center colspan=1 id="elm">:</td>
                    <td align=center colspan=1 id="tsl_ir_luminosity">00</td>
                    <td align=center colspan=3 id="unit"></td>
                </tr>                
            </table>
        </div>
    </div>
</body>
</html>