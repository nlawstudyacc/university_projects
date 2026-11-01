defmodule Shunt do
  def find(_, []) do
    []
  end
  def find(currentTrainXSegment, [desiredWagon|restOfTrainY]) do
    {beforeDeisredWagon, afterDesiredWagon} = Train.split(currentTrainXSegment, desiredWagon)
    lengthOfMovementToOne = length(afterDesiredWagon) + 1
    lengthOfMovementToTwo = length(beforeDeisredWagon)
    {movementTrackOne, movementTrackTwo} = {[desiredWagon|afterDesiredWagon], beforeDeisredWagon}
    [_insertedWagon|remainingTrackToAnalyze] = Train.append(movementTrackOne, movementTrackTwo)
    [{:one, lengthOfMovementToOne}, {:two, lengthOfMovementToTwo}, {:one, -lengthOfMovementToOne}, {:two, -lengthOfMovementToTwo}|find(remainingTrackToAnalyze, restOfTrainY)]
  end

  def few(_, []) do
    []
  end
  def few([similarWagon|restOfCurrentSegmentX], [similarWagon|restOfTrainY]) do
    few(restOfCurrentSegmentX, restOfTrainY)
  end
  def few(currentTrainXSegment, [desiredWagon|restOfTrainY]) do
    {beforeDeisredWagon, afterDesiredWagon} = Train.split(currentTrainXSegment, desiredWagon)
    lengthOfMovementToOne = length(afterDesiredWagon) + 1
    lengthOfMovementToTwo = length(beforeDeisredWagon)
    {movementTrackOne, movementTrackTwo} = {[desiredWagon|afterDesiredWagon], beforeDeisredWagon}
    [_insertedWagon|remainingTrackToAnalyze] = Train.append(movementTrackOne, movementTrackTwo)
    [{:one, lengthOfMovementToOne}, {:two, lengthOfMovementToTwo}, {:one, -lengthOfMovementToOne}, {:two, -lengthOfMovementToTwo}|few(remainingTrackToAnalyze, restOfTrainY)]
  end

  def fewer({mainTrain, trainOne, trainTwo}, trainY) do

  end

  def rules([]) do
    []
  end
  def rules([{_, 0}|remainingMoves]) do
    rules(remainingMoves)
  end
  def rules([{trackNumber, n}|[{trackNumber, m}|remainingMoves]]) do
    [{trackNumber, n + m}|rules(remainingMoves)]
  end
  def rules([headMove|remainingMoves]) do
    [headMove|rules(remainingMoves)]
  end

  def compress(ms) do
    ns = rules(ms)
    if ns == ms do
      ms
    else
      compress(ns)
    end
  end
end
