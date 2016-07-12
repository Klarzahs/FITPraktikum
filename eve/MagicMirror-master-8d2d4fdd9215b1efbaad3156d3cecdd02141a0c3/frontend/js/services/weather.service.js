(function () {

    function weatherService ($http, $q) {
        var service = {};
        service.getSensorData = getSensorData;

        function getSensorData () {
            var deferred = $q.defer();
            $http.get('/api/bmpTable?sort=-_updated').then(function (tempData) {
                var temperature = tempData.data._items[0] ? tempData.data._items[0].Temperature : "Nothing to show.";
                $http.get('/api/humidity?sort=-_updated').then(function (humData) {
                    var humidity = humData.data._items[0] ? humData.data._items[0].value : "Nothing to show.";
                    $http.get('/api/pressure?sort=-_updated').then(function (presData) {
                        var pressure = presData.data._items[0] ? presData.data._items[0].value : "Nothing to show.";
                        deferred.resolve({
                            temperature : temperature,
                            humidity  : humidity,
                            pressure : pressure
                        });
                    });
                });
            });
            return deferred.promise;
        }

        function getOpenWeatherMapData () {
            // rest call todo
        }

        return service;
    }

    weatherService.$inject = ['$http', '$q'];

    angular.module("mirror").factory("weatherService", weatherService);
})();
