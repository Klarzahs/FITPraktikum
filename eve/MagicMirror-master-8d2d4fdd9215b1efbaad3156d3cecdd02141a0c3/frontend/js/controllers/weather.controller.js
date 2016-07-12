(function () {
    function weatherController ( $scope, $interval, weatherService ) {
        $scope.temperature = undefined;
        $scope.pressure = undefined;
        $scope.humidity = undefined;

        function setData() {
            weatherService.getSensorData().then(function (data) {
                $scope.temperature = data.temperature;
                $scope.pressure = data.pressure;
                $scope.humidity = data.humidity;
            });
        }

        setData();

        $interval(function () {
            setData();
        }, 5000);

    }

    weatherController.$inject = ['$scope', '$interval', 'weatherService'];

    angular.module("mirror").controller('weatherController', weatherController)
})();
