setInterval(function(){
            $(document).ready(function() {  
                
                $.ajax({
                    url: 'js/getdata.php',
                    type: 'GET',
                    dataType: 'json',
                    error: function (xhr, status, err) {
                        console.error("error");
                        }.bind(this),
                    success: function(response){
                        var datalist = response;

                        var tsl_full_luminosity = datalist.tsl_full_luminosity;
                        var tsl_lux = datalist.tsl_lux;
                        var tsl_ir_luminosity = datalist.tsl_ir_luminosity;

                        var bmp_temperature = datalist.bmp_temperature;
                        var bmp_altitude = datalist.bmp_altitude;
                        var bmp_pressure = datalist.bmp_pressure;
                        var bmp_sea_level_pressure = datalist.bmp_sea_level_pressure;

                        var dht_temperature = datalist.dht_temperature;
                        var dht_humidity = datalist.dht_humidity;

                        var time = new Date();
                        var hour = time.getHours();
                        if (dht_temperature > 25) {
                            if(hour>6 && hour<20){
                                $('#weather_icon').attr('src', '../magicmirror/img/sun.png');   
                            }else{
                                $('#weather_icon').attr('src', '../magicmirror/img/moon.png');
                            };
                        }else if(dht_temperature < 8){
                            $('#weather_icon').attr('src', '../magicmirror/img/cold.png');
                        }else{
                            if(hour>6 && hour<20){
                                $('#weather_icon').attr('src', '../magicmirror/img/sun_cloud.png');   
                            }else{
                                $('#weather_icon').attr('src', '../magicmirror/img/moon_cloud.png');
                            };
                        };

                        $('#tsl_full_luminosity').html(tsl_full_luminosity);
                        $('#tsl_lux').html(tsl_lux);
                        $('#tsl_ir_luminosity').html(tsl_ir_luminosity);

                        $('#bmp_temperature').html(bmp_temperature);
                        $('#bmp_altitude').html(bmp_altitude);
                        $('#bmp_pressure').html(bmp_pressure);
                        $('#bmp_sea_level_pressure').html(bmp_sea_level_pressure);

                        $('#dht_temperature').html(dht_temperature);
                        $('#dht_humidity').html(dht_humidity);                       
                        console.log(tsl_full_luminosity);
                    }
                });                   
            });
        }, 10000); 