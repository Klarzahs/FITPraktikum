<?php
        function getLastPageLink($url){
                $file = file_get_contents($url);

                $temp = explode('last": {"href": "', $file);
                $lastpage = explode('", "title": "last page"', $temp[1]);
                $lastpagelink = 'http://172.17.0.3:5000/'.$lastpage[0];
                return $lastpagelink;
        }


        $link_bmp = 'http://172.17.0.5:5000/bmpTable?sort=-Timestamp';
        $link_tsl = 'http://172.17.0.5:5000/tslTable?sort=-Timestamp';
        $link_dht = 'http://172.17.0.5:5000/dhtTable?sort=-Timestamp';

        //Latest data
        //TSL raw
        $lastpage = file_get_contents($link_tsl);
        $id_tsl = explode('_id', $lastpage);
        $latest_tsl_data = $id_tsl[0];
        //BMP raw
        $lastpage = file_get_contents($link_bmp);
        $id_bmp = explode('_id', $lastpage);
        $latest_bmp_data = $id_bmp[0];
        //DHT raw
        $lastpage = file_get_contents($link_dht);
        $id_dht = explode('_id', $lastpage);
        $latest_dht_data = $id_dht[0];

        //TSL data
        $tsl_full_luminosity = explode('full_luminosity": ', $latest_tsl_data);
        $tsl_full_luminosity = explode(', "Lux":',$tsl_full_luminosity[1]);
        $tsl_full_luminosity = $tsl_full_luminosity[0];

        $tsl_lux = explode('"Lux": ', $latest_tsl_data);
        $tsl_lux = explode(', "_links"',$tsl_lux[1]);
        $tsl_lux = $tsl_lux[0];

        $tsl_ir_luminosity = explode('"ir_luminosity": ', $latest_tsl_data);
        $tsl_ir_luminosity = explode(', "', $tsl_ir_luminosity[1]);
        $tsl_ir_luminosity = $tsl_ir_luminosity[0];

        //BMP data
        $bmp_temperature = explode('"Temperature": ', $latest_bmp_data);
        $bmp_temperature = explode(', "Altitude"',$bmp_temperature[1]);
        $bmp_temperature = $bmp_temperature[0];

        $bmp_altitude = explode('"Altitude": ', $latest_bmp_data);
        $bmp_altitude = explode(', "Pressure"',$bmp_altitude[1]);
        $bmp_altitude = $bmp_altitude[0];

        $bmp_pressure = explode('"Pressure": ', $latest_bmp_data);
        $bmp_pressure = explode(', "sea_level_pressure"',$bmp_pressure[1]);
        $bmp_pressure = $bmp_pressure[0];

        $bmp_sea_level_pressure = explode('"sea_level_pressure": ', $latest_bmp_data);
        $bmp_sea_level_pressure = explode(', "_links"',$bmp_sea_level_pressure[1]);
        $bmp_sea_level_pressure = $bmp_sea_level_pressure[0];

        //DHT
        $dht_temperature = explode('"Temperature": ', $latest_dht_data);
        $dht_temperature = explode(', "Humidity"',$dht_temperature[1]);
        $dht_temperature = $dht_temperature[0];

        $dht_humidity = explode('"Humidity": ', $latest_dht_data);
        $dht_humidity = explode(', "_links"',$dht_humidity[1]);
        $dht_humidity = $dht_humidity[0];

        $datalist = array(
                'tsl_full_luminosity' => $tsl_full_luminosity,
                'tsl_lux' => $tsl_lux,
                'tsl_ir_luminosity' => $tsl_ir_luminosity,
                'bmp_temperature' => $bmp_temperature,
                'bmp_altitude' => $bmp_altitude,
                'bmp_pressure' => $bmp_pressure,
                'bmp_sea_level_pressure' => $bmp_sea_level_pressure,
                'dht_temperature' => $dht_temperature,
                'dht_humidity' => $dht_humidity
                );

        echo json_encode($datalist);
?>
