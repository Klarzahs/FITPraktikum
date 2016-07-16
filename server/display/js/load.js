setInterval(function(){
            $(document).ready(function() {  
                 $.simpleWeather({
                    location: 'Aachen, Germany',
                    woeid: '',
                    unit: 'C',
                    success: function(weather) {
                      html = '<h2>'+weather.temp+'&deg;'+weather.units.temp+'</h2>';
                      html += '<ul><li>'+weather.city+', '+weather.region+'</li>';
                      html += '<li class="currently">'+weather.currently+'</li>';
                      html += '<li>'+weather.alt.temp+'&deg;C</li></ul>';
                      
                      for(var i=0;i<weather.forecast.length;i++) {
                        html += '<p>'+weather.forecast[i].day+': '+weather.forecast[i].high+'</p>';
                      }
                  
                      $("#weather").html(html);
                    },
                    error: function(error) {
                      $("#weather").html('<p>'+error+'</p>');
                    }
                  });

                
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
                        var tsl_lux = parseFloat(datalist.tsl_lux.split(",")[0]).toFixed(2);
                        var tsl_ir_luminosity = datalist.tsl_ir_luminosity;

                        var bmp_temperature = parseFloat(datalist.bmp_temperature.split(",")[0]).toFixed(2);
                        var bmp_altitude = datalist.bmp_altitude / 1000;
                        var bmp_pressure = datalist.bmp_pressure.split(",")[0];
                        var bmp_sea_level_pressure = datalist.bmp_sea_level_pressure;

                        var dht_temperature = datalist.dht_temperature.split(",")[0];
                        var dht_humidity = datalist.dht_humidity;

                        var time = new Date();
                        var hour = time.getHours();
                        if (dht_temperature > 25) {
                            if(hour>6 && hour<20){
                                $('#weather_icon').attr('src', '../img/sun.png');   
                            }else{
                                $('#weather_icon').attr('src', '../img/moon.png');
                            };
                        }else if(dht_temperature < 8){
                            $('#weather_icon').attr('src', '../img/cold.png');
                        }else{
                            if(hour>6 && hour<20){
                                $('#weather_icon').attr('src', '../img/sun_cloud.png');   
                            }else{
                                $('#weather_icon').attr('src', '../img/moon_cloud.png');
                            };
                        };

                        $('#tsl_full_luminosity').html(tsl_full_luminosity);
                        $('#tsl_lux').html(tsl_lux);
                        $('#tsl_ir_luminosity').html(tsl_ir_luminosity);

                        $('#bmp_temperature').html(bmp_temperature);
                        $('#bmp_altitude').html(bmp_altitude);
                        $('#bmp_pressure').html(bmp_pressure);

                        $('#dht_temperature').html(dht_temperature);
                        $('#dht_humidity').html(dht_humidity);                       
                        console.log(tsl_full_luminosity);
                    }
                });                   
            });
        }, 10000); 