defmodule Moves do
  def single({:one, wagonsAmount}, {mainTrain, trainOne, trainTwo}) when wagonsAmount >= 0 do
    {_, remain, take} = Train.main(mainTrain, wagonsAmount)
    {remain, Train.append(take, trainOne), trainTwo}
  end
  def single({:one, wagonsAmount}, {mainTrain, trainOne, trainTwo}) do
    {takeWagons, trainOne} = {Train.take(trainOne, abs(wagonsAmount)), Train.drop(trainOne, abs(wagonsAmount))}
    {Train.append(mainTrain, takeWagons), trainOne, trainTwo}
  end
  def single({:two, wagonsAmount}, {mainTrain, trainOne, trainTwo}) when wagonsAmount >= 0 do
    {_, remain, take} = Train.main(mainTrain, wagonsAmount)
    {remain, trainOne, Train.append(take, trainTwo)}
  end
  def single({:two, wagonsAmount}, {mainTrain, trainOne, trainTwo}) do
    {takeWagons, trainTwo} = {Train.take(trainTwo, abs(wagonsAmount)), Train.drop(trainTwo, abs(wagonsAmount))}
    {Train.append(mainTrain, takeWagons), trainOne, trainTwo}
  end

  def sequence([], trainTrack) do
    trainTrack
  end
  def sequence([headCommand|tailCommands], trainTrack) do
    changedTrack = single(headCommand, trainTrack)
    [trainTrack|sequence(tailCommands, changedTrack)]
  end
end
