<?hh //strict

namespace CodeCampExport\Generators;

use Plenty\Modules\DataExchange\Contracts\CSVGenerator;
use Plenty\Modules\Helper\Services\ArrayHelper;
use Plenty\Modules\Item\DataLayer\Models\Record;
use Plenty\Modules\Item\DataLayer\Models\RecordList;
use Plenty\Modules\DataExchange\Models\FormatSetting;

use CodeCampExport\Helpers\ExportHelper;

class AwesomeMarketplaceGenerator extends CSVGenerator
{
	/**
	 * ArrayHelper $arrayHelper
	 */
	private ArrayHelper $arrayHelper;

	/**
	 * ExportHelper $exportHelper
	 */
	private ExportHelper $exportHelper;

	/**	 
	 * @param ArrayHelper $arrayHelper
	 * @param ExportHelper $exportHelper	 
	 */
	public function __construct(ArrayHelper $arrayHelper, ExportHelper $exportHelper)
	{
		$this->arrayHelper = $arrayHelper;
		$this->exportHelper = $exportHelper;
	}

	protected function generateContent(mixed $resultData, array<FormatSetting> $formatSettings = []):void
	{
		$this->setDelimiter("|");

		if($resultData instanceof RecordList)
		{
			$settings = $this->arrayHelper->buildMapFromObjectList($formatSettings, 'key', 'value');

			$this->addCSVContent([
					'id',					
					'name',
					'description',
					'price',					
					'stock',					
			]);

			foreach($resultData as $item)
			{
				$data = [
					'id' 				=> $item->itemBase->id,					
					'name' 				=> $this->exportHelper->getName($item, $settings),
					'description' 		=> $this->exportHelper->getDescription($item, $settings),					
					'price' 			=> $item->variationRetailPrice->price,										
					'stock' 			=> $item->variationStock->stockNet,					
				];

				$this->addCSVContent(array_values($data));
			}			
		}
	}	
}