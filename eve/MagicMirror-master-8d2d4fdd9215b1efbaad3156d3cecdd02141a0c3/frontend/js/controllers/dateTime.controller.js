(function () {
    function dateTimeController ( $scope, $interval ) {
        $scope.currentTime = moment().format('MMMM Do YYYY, h:mm:ss a');

        $interval(function () {
            $scope.currentTime = moment().format('MMMM Do YYYY, h:mm:ss a');
        }, 1000);
    }

    dateTimeController.$inject = ['$scope', '$interval'];

    angular.module("mirror").controller('dateTimeController', dateTimeController)
})();
