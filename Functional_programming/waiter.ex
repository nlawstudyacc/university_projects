defmodule Waiter do
  def start() do
    spawn_link(fn -> request() end)
  end

  #requestInformation == {philosopherPID, hungerValue, leftStick, rightStick}
  def request() do
    receive do
      {philosopherPID, leftStick, rightStick} ->
        send(leftStick, {:requestWaiter, self()})
        send(rightStick, {:requestWaiter, self()})
        processRequest(philosopherPID)
    end
  end

  def processRequest(philosopherPID) do
    receive do
      :granted ->
        receive do
          :granted ->
            send(philosopherPID, :ok)
            request()
          :denied ->
            send(philosopherPID, :no)
            request()
        end
      :denied ->
        :no
        send(philosopherPID, :no)
        request()
    end
  end
end
